#include "renderer.h"

#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <stdio.h>

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

bool isPrintable(wchar_t character){
    return !(character >= 0 && character <= 32 || character == 127);
}

wchar_t* getPrintable(wchar_t content){
    if(!(content >= 0 && content <= 32 || content == 127)) return L"   ";

    switch (content){
    case 0: return   L"NUL (null)";
    case 1: return   L"SOH (start of heading)";
    case 2: return   L"STX (start of text)";
    case 3: return   L"ETX (end of text)";
    case 4: return   L"EOT (end of transmission)";
    case 5: return   L"ENQ (enquiry)";
    case 6: return   L"ACK (acknowledge)";
    case 7: return   L"BEL (bell)";
    case 8: return   L"BS  (backspace)";
    case 9: return   L"TAB (horizontal tab)";
    case 10: return  L"LF  (NL line feed, new line)";
    case 11: return  L"VT  (vertical tab)";
    case 12: return  L"FF  (NP form feed, new page)";
    case 13: return  L"CR  (carriage return)";
    case 14: return  L"SO  (shift out)";
    case 15: return  L"SI  (shift in)";
    case 16: return  L"DLE (data link escape)";
    case 17: return  L"DC1 (device control 1)";
    case 18: return  L"DC2 (device control 2)";
    case 19: return  L"DC3 (device control 3)";
    case 20: return  L"DC4 (device control 4)";
    case 21: return  L"NAK (negative acknowledge)";
    case 22: return  L"SYN (synchronous idle)";
    case 23: return  L"ETB (end of trans. block)";
    case 24: return  L"CAN (cancel)";
    case 25: return  L"EM  (end of medium)";
    case 26: return  L"SUB (substitute)";
    case 27: return  L"ESC (escape)";
    case 28: return  L"FS  (file separator)";
    case 29: return  L"GS  (group separator)";
    case 30: return  L"RS  (record separator)";
    case 31: return  L"US  (unit separator)";
    case 32: return  L"SPACE";
    case 127:return  L"DEL (delete control)";
    default: return  L"   ";
    }
}

void _renderTable(asciiParams params){
    // _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    uint8_t col = (params.contentSize%MAX_ROW) == 0?(params.contentSize/MAX_ROW):(params.contentSize/MAX_ROW)+1;
    uint8_t row = col > 1?MAX_ROW:params.contentSize;
    
    uint8_t* maxLength = (uint8_t*) calloc(col,sizeof(uint8_t));
    wstring* lines = new wstring[row];
    size_t s = 0;

    uint8_t currRow = s%row;
    uint8_t currCol = (s/row)+1;
    uint8_t procCol = 0;
    uint8_t currLineLength = 0;

    while(params.contentSize - s){
        wchar_t tmp[100];
        currRow = s%row;
        currCol = (s/row)+1;

        if(currCol != procCol){
            for(uint8_t i = 0; i < row && s+i < params.contentSize; i++){
                currLineLength = wcslen( getPrintable(params.content[s+i]) ) - 3;
                maxLength[currCol-1] = maxLength[currCol-1] < currLineLength?currLineLength:maxLength[currCol-1];
            }
            procCol = currCol;
        }

        if(params.onlyOct || params._onlyAll){
            snwprintf(tmp, sizeof(tmp), L"%03o  ", params.content[s]);
            lines[currRow] += tmp;
        }

        if(params.onlyDec || params._onlyAll){
            snwprintf(tmp, sizeof(tmp), L"%3d  ", params.content[s]);
            lines[currRow] += tmp;
        }

        if(params.onlyHex || params._onlyAll){
            snwprintf(tmp, sizeof(tmp), L" %2X  ", params.content[s]);
            lines[currRow] += tmp;
        }

        if(params.onlyBin /*|| params._onlyAll*/){
            uint8_t index = 0; wchar_t content = params.content[s];
            wstring binStr = L"0000 0000\0";

            for(uint8_t i = 128; i > 0 && content != 0; ){
                if(binStr[index] == L' '){
                    index++;
                    continue;
                }

                if(content >= i){
                    binStr[index] = L'1';
                    content -= i;
                }

                index++;
                i=(i/2);
            }
            
            snwprintf(tmp, sizeof(tmp), L"%ls  ",  binStr);
            lines[currRow] += tmp;
        }

        if(isPrintable(params.content[s])){
            snwprintf(tmp, sizeof(tmp),L"" YEL "%c " RESET, params.content[s]);
            currLineLength = 0;
        }else{
            wchar_t* print = getPrintable(params.content[s]);
            currLineLength = wcslen(print) - 3;
            snwprintf(tmp, sizeof(tmp),L"" YEL "%ls" RESET, print);
        }
        if(params.onlyChar || params._onlyAll) lines[currRow] += tmp;

        if(currCol != col){
            wchar_t* spaces = (wchar_t*)calloc( (size_t)maxLength[currCol-1] - currLineLength +1,sizeof(wchar_t));
            wmemset(spaces, (wchar_t)32, (size_t)maxLength[currCol-1] - currLineLength);

            lines[currRow] += spaces;
            lines[currRow] += (currLineLength == 0?L"  ":L" ");
            lines[currRow] += (wchar_t)_VL_1;lines[currRow] += L"  ";

            free(spaces);
        }
        s++;
    }

    uint16_t colLineLength = (params.onlyOct || params._onlyAll?5:0) + (params.onlyDec || params._onlyAll?5:0) + (params.onlyHex || params._onlyAll?5:0) + (params.onlyBin /*|| params._onlyAll*/?11:0) + (params.onlyChar || params._onlyAll?5:0);
    
    wcout<<(wchar_t)_E;
    for(uint8_t i = 0; i < col; i++){
        wcout<<wstring(maxLength[i],(wchar_t)_HL_1)<<wstring( (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)),(wchar_t)_HL_1 );
        if(col-1 != i) wcout<<(wchar_t)_IT_1<<(wchar_t)_HL_1<<(wchar_t)_HL_1;        
    }wcout<<"\n" RESET<<(wchar_t)_E;

    for(uint8_t i = 0; i < col; i++){
        if(params.onlyOct || params._onlyAll)  wcout<<"Oct  ";
        if(params.onlyDec || params._onlyAll)  wcout<<"Dec  ";
        if(params.onlyHex || params._onlyAll)  wcout<<"Hex  ";
        if(params.onlyBin /*|| params._onlyAll*/)  wcout<<"Binary     ";
        if(params.onlyChar|| params._onlyAll)  wcout<<YEL "Chr" RESET;

        if(col != i+1){
            wcout<<(wchar_t)_E<<wstring(maxLength[i],(wchar_t)_E)<<(wchar_t)_VL_1<<(wchar_t)_E<<(wchar_t)_E;
        }
    }wcout<<"\n" RESET<<(wchar_t)_E;

    for(uint8_t i = 0; i < col; i++){
        wcout<<wstring(maxLength[i],(wchar_t)_HL_1)<<wstring( (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)),(wchar_t)_HL_1 );
        if(col-1 != i) wcout<<(wchar_t)_IC_1<<(wchar_t)_HL_1<<(wchar_t)_HL_1;        
    }wcout<<"\n" RESET;

    for(uint8_t i = 0; i < row; i++){
        wcout<<(wchar_t)_E<<lines[i]<<endl<<RESET;
    }wcout<<RESET<<(wchar_t)_E;

    for(uint8_t i = 0; i < col; i++){
        wcout<<wstring(maxLength[i],(wchar_t)_HL_1)<<wstring( (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)),(wchar_t)_HL_1 );
        if(col-1 != i) wcout<<(wchar_t)_IB_1<<(wchar_t)_HL_1<<(wchar_t)_HL_1;         
    }wcout<<"\n" RESET;
}
