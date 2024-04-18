// DLLExample.cpp
#include "tablePartial.h"
#include <iostream>
#include <iomanip>
#include <stdint.h>

#include <io.h>
#include <fcntl.h>

using namespace std;

enum _BR{
    _HL_1  = L'─',
    _VL_1  = L'│',
    _TLC_1 = L'╭',
    _TRC_1 = L'╮',
    _BLC_1 = L'╰',
    _BRC_1 = L'╯',
    _IL_1  = L'├',
    _IR_1  = L'┤',
    _IC_1  = L'┼',
    _IT_1  = L'┬',
    _IB_1  = L'┴',
    _E     = L' '
};

void _renderTable(Table* table){
    // _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(handle, &csbi);
    COORD basePosition = csbi.dwCursorPosition;
    COORD currPosition = basePosition;

    currPosition.X += 2;
    for(uint8_t i = 0; i < table->colSize; i++){
        Column* column = table->columns[i];

        currPosition.Y = basePosition.Y;
        SetConsoleCursorPosition(handle, currPosition);

        uint8_t lineLength = (column->_toShink?  column->shrinkHeaderSize: column->maxHeaderSize? column->maxHeaderSize :strlen(column->header) );
        lineLength = lineLength > column->length?lineLength:column->length;

        wcout<<wstring( lineLength ,(wchar_t)_HL_1);
        if(i != table->colSize-1 && (column->border == RIGHT || column->border == LEFT_RIGHT || table->columns[i+1]->border == LEFT) ) wcout<<(wchar_t)_HL_1<<(wchar_t)_IT_1<<(wchar_t)_HL_1; else wcout<<(wchar_t)_HL_1;
        
        currPosition.Y += 1;
        SetConsoleCursorPosition(handle, currPosition);
        
        if(i != table->colSize-1 && (column->border == RIGHT || column->border == LEFT_RIGHT) ) wcout<<(wchar_t)_E<<(wchar_t)_VL_1;

        wcout<< (
            column->_toShink?  wstring(column->header, &column->header[column->shrinkHeaderSize])  :
            column->maxHeaderSize? wstring(column->header, &column->header[column->maxHeaderSize]) :
            wstring(column->header, &column->header[ strlen(column->header) ])
        );

        if(i != table->colSize-1 && table->columns[i+1]->border == LEFT ) wcout<<(wchar_t)_E<<(wchar_t)_VL_1;

        currPosition.Y += 1;
        SetConsoleCursorPosition(handle, currPosition);

        wcout<<wstring(lineLength,(wchar_t)_HL_1);
        if(i != table->colSize-1 && (column->border == RIGHT || column->border == LEFT_RIGHT || table->columns[i+1]->border == LEFT) ) wcout<<(wchar_t)_HL_1<<(wchar_t)_IC_1<<(wchar_t)_HL_1; else wcout<<(wchar_t)_HL_1;
        currPosition.Y += 1;

        while( column->_curr != NULL ){
            SetConsoleCursorPosition(handle, currPosition);
            
            if(i != 0 && column->border == RIGHT || column->border == LEFT_RIGHT) wcout<<(wchar_t)_E<<(wchar_t)_VL_1;
            wcout<< column->_curr->data;
            if(i != table->colSize-1 && table->columns[i+1]->border == LEFT ){
                uint8_t oheaderLength = (column->_toShink? column->shrinkHeaderSize : column->maxHeaderSize? column->maxHeaderSize : strlen(column->header));
                
                wcout<<wstring(abs(oheaderLength-column->_curr->length),L' ');
                wcout<<(wchar_t)_E<<(wchar_t)_VL_1;
            }


            column->_curr = column->_curr->_next;
            currPosition.Y += 1;
        }

        SetConsoleCursorPosition(handle, currPosition);
        wcout<<wstring(lineLength,(wchar_t)_HL_1);
        if(i != table->colSize-1 && (column->border == RIGHT || column->border == LEFT_RIGHT || table->columns[i+1]->border == LEFT) ) wcout<<(wchar_t)_HL_1<<(wchar_t)_IB_1<<(wchar_t)_HL_1; else wcout<<(wchar_t)_HL_1;
        
        currPosition.X += lineLength;
        currPosition.X += column->border == RIGHT || column->border == LEFT_RIGHT
                        ||(i != table->colSize-1 && table->columns[i+1]->border == LEFT)?3: 1;
    }

    SHORT lastX = currPosition.X;
    for(uint8_t side = 0; side <= 1; side++){
    currPosition = basePosition;
    if(side == 1) currPosition.X = lastX;
    for(uint8_t i = 0; i < table->rowSize+4; i++){
        SetConsoleCursorPosition(handle, currPosition);
        if      (i == 0 && side == 0) wcout<<(wchar_t)_TLC_1<<(wchar_t)_HL_1;
        else if (i == table->rowSize+3 && side == 0) wcout<<(wchar_t)_BLC_1<<(wchar_t)_HL_1;
        else if (i == 0 && side == 1) wcout<<(wchar_t)_HL_1<<(wchar_t)_TRC_1;
        else if (i == table->rowSize+3 && side == 1) wcout<<(wchar_t)_HL_1<<(wchar_t)_BRC_1;
        else if (side == 1) wcout<<(wchar_t)_E<<(wchar_t)_VL_1;
        else wcout<<(wchar_t)_VL_1;
        currPosition.Y++;
    }
    }

}
