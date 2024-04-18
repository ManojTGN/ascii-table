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
    _E     = L' '
};

void _renderHeader(Table* table, _renderInfo* renderInfo){
    wstring wborderLine = wstring(table->length+1,_HL_1);
    wcout<<(wchar_t)_TLC_1<<wborderLine<<(wchar_t)_TRC_1<<endl<<(wchar_t)_VL_1<<(wchar_t)_E;
    
    for(uint8_t i =0; i < table->colSize; i++){
        if(table->columns[i]->_toShink){
            wcout<<wstring(table->columns[i]->header, &table->columns[i]->header[ table->columns[i]->shrinkHeaderSize ])<<(wchar_t)_E;
        }else if(table->columns[i]->maxHeaderSize == 0 && table->columns[i]->length >= strlen(table->columns[i]->header)){
            wcout<<table->columns[i]->header<<(wchar_t)_E;
        }else if(table->columns[i]->maxHeaderSize != 0){
            wcout<<wstring(table->columns[i]->header, &table->columns[i]->header[ table->columns[i]->maxHeaderSize ])<<(wchar_t)_E;
        }else{
            wcout<<table->columns[i]->header<<(wchar_t)_E;
        }
    }wcout<<(wchar_t)_VL_1<<endl<<(wchar_t)_IL_1<<wborderLine<<(wchar_t)_IR_1<<endl;
}

void _renderBody(Table* table, _renderInfo* renderInfo){
    wstring wborderLine = wstring(table->length+1,_HL_1);

    for(uint8_t j = 0; j < table->rowSize; j++){
        wcout<<(wchar_t)_VL_1<<(wchar_t)_E;
        for(uint8_t i = 0; i < table->colSize; i++){
            if(table->columns[i]->_curr == NULL) continue;
            
            wcout<<wstring(table->columns[i]->_curr->data)<<(wchar_t)_E;

            if(table->columns[i]->maxHeaderSize == 0 && table->columns[i]->length >= strlen(table->columns[i]->header)){
                wcout<<wstring(abs( (int)(strlen(table->columns[i]->header)-(int)table->columns[i]->_curr->length) ),(wchar_t)_E)<<(wchar_t)_E;
            }else if(table->columns[i]->maxHeaderSize != 0 && table->columns[i]->_curr->length < table->columns[i]->maxHeaderSize ){
                wcout<<wstring(table->columns[i]->maxHeaderSize - table->columns[i]->_curr->length,(wchar_t)_E)<<(wchar_t)_E;
            }else{
                // wcout<<table->columns[i]->header<<(wchar_t)_E;
            }

            table->columns[i]->_curr = table->columns[i]->_curr->_next;
        }
        wcout<<(wchar_t)_VL_1<<endl;
    }

    wcout<<(wchar_t)_BLC_1<<wborderLine<<(wchar_t)_BRC_1<<endl;
}

void _renderTable(Table* table){
    // _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    _renderInfo renderInfo = {};
    
    _renderHeader(table, &renderInfo);
    _renderBody(table, &renderInfo);
    
}
