#include "renderer.h"

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
    wstring lines[ (table->rowSize > table->maxRows?table->maxRows:table->rowSize) ];
    uint8_t rowRendered = 0;
    uint8_t colRendered = 1;

    for(uint8_t i =0 ; i < table->colSize; i++){
        wcout<< table->columns[i]->title<<L":";
        for(uint8_t j = 0; j < MAX_COLUMNS; j++) wcout<<table->columns[i]->totalLength[j]<<L" ";
        wcout<<endl;
    }

    uint8_t tmpLength = 1;
    wstring borderLine = wstring( table->totalLength + (table->colSize * 6) + 1,(wchar_t)_HL_1);
    
    for(uint8_t j = 0; j < MAX_COLUMNS; j++){
        for(uint8_t i =0 ; i < table->colSize; i++){
            tmpLength += table->columns[i]->totalLength[j];
        }
        
        tmpLength += 4;
        borderLine[tmpLength] = _IT_1;
        tmpLength += 2;
    }

    wcout<<endl<<(wchar_t)_E<<borderLine<<endl;

    while(rowRendered != table->rowSize){
        for(uint8_t i = 0; i < table->maxRows; i++){
        if(colRendered == 1) lines[i] += wstring(2,(wchar_t)_E);
        for(uint8_t j = 0; j < table->colSize; j++){
            if(table->columns[j]->_curr == NULL) continue;


            lines[i] += table->columns[j]->_curr->data;
            lines[i] += wstring(table->columns[j]->totalLength[rowRendered/MAX_ROWS] - table->columns[j]->_curr->length + 1, L' ');

            if(j == table->colSize-1 && colRendered != table->colSize){
                lines[i]+= _VL_1;
                lines[i]+= _E;
            }

            table->columns[j]->_curr = table->columns[j]->_curr->_next;
        }   rowRendered++;
        }
        colRendered++;
    }

    for(uint8_t i = 0; i < (table->rowSize > table->maxRows?table->maxRows:table->rowSize) ; i++)
        wcout<<lines[i]<<endl;
    
    tmpLength = 1;
    for(uint8_t j = 0; j < MAX_COLUMNS; j++){
        for(uint8_t i =0 ; i < table->colSize; i++){
            tmpLength += table->columns[i]->totalLength[j];
        }
        
        tmpLength += 4;
        borderLine[tmpLength] = _IB_1;
        tmpLength += 2;
    }


    wcout<<(wchar_t)_E<<borderLine<<endl;

}
