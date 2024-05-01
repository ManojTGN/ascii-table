#include "ascii.h"

typedef void (*_renderTable)(asciiParams params);

/**
 * @brief printing the content into table format
 * 
 * @param params 
 */
void renderTable(asciiParams params){
    uint8_t col = (params.contentSize%MAX_ROW) == 0?(params.contentSize/MAX_ROW):(params.contentSize/MAX_ROW)+1;
    uint8_t row = col > 1?MAX_ROW:params.contentSize;
    
    uint8_t* maxLength = (uint8_t*) calloc(col,sizeof(uint8_t));
    wchar_t** lines = (wchar_t**)calloc(row,sizeof(wchar_t*));
    size_t s = 0;

    for(uint8_t i = 0; i < row; i++)
        lines[i] = (wchar_t*)calloc(300,sizeof(wchar_t));

    uint8_t currRow = s%row;
    uint8_t currCol = (s/row)+1;
    uint8_t procCol = 0;
    uint8_t currLineLength = 0;

    while(params.contentSize - s){
        wchar_t tmp[60];
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
            wcscat(lines[currRow],tmp);
        }

        if(params.onlyDec || params._onlyAll){
            snwprintf(tmp, sizeof(tmp), L"%3d  ", params.content[s]);
            wcscat(lines[currRow],tmp);
        }

        if(params.onlyHex || params._onlyAll){
            snwprintf(tmp, sizeof(tmp), L" %2X  ", params.content[s]);
            wcscat(lines[currRow],tmp);
        }

        if(params.onlyBin /*|| params._onlyAll*/){
            uint8_t index = 0; wchar_t content = params.content[s];
            wchar_t binStr[10] = L"0000 0000\0";

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
            wcscat(lines[currRow],tmp);
        }

        if(isPrintable(params.content[s])){
            snwprintf(tmp, sizeof(tmp),L""YEL"%c "RESET, params.content[s]);
            currLineLength = 0;
        }else{
            wchar_t* print = getPrintable(params.content[s]);
            currLineLength = wcslen(print) - 3;
            snwprintf(tmp, sizeof(tmp),L""YEL"%ls"RESET, print);
        }
        if(params.onlyChar || params._onlyAll) wcscat(lines[currRow],tmp);

        if(currCol != col){
            wchar_t* spaces = (wchar_t*)calloc( (size_t)maxLength[currCol-1] - currLineLength +1,sizeof(wchar_t));
            wmemset(spaces, (wchar_t)32, (size_t)maxLength[currCol-1] - currLineLength);

            wcscat(lines[currRow],spaces);
            wcscat(lines[currRow],currLineLength == 0?L"  |  ":L" |  ");

            free(spaces);
        }
        s++;
    }

    uint16_t colLineLength = (params.onlyOct || params._onlyAll?5:0) + (params.onlyDec || params._onlyAll?5:0) + (params.onlyHex || params._onlyAll?5:0) + (params.onlyBin /*|| params._onlyAll*/?11:0) + (params.onlyChar || params._onlyAll?5:0);
    
    for(uint8_t i = 0; i < col; i++){
        if(params.onlyOct || params._onlyAll)  wprintf(L"Oct  ");
        if(params.onlyDec || params._onlyAll)  wprintf(L"Dec  ");
        if(params.onlyHex || params._onlyAll)  wprintf(L"Hex  ");
        if(params.onlyBin /*|| params._onlyAll*/)  wprintf(L"Binary     ");
        if(params.onlyChar|| params._onlyAll)  wprintf(L""YEL"Chr"RESET);

        if(col != i+1){
            uint8_t* spaces = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
            memset(spaces, (uint8_t)32, sizeof(uint8_t) * (size_t)maxLength[i]);

            wprintf(L" %s|  ",spaces);
            free(spaces);
        }
    }wprintf(L"\n"RESET);

    for(uint8_t i = 0; i < col; i++){
        uint8_t* hyphens = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
        memset(hyphens, (uint8_t)45, sizeof(uint8_t) * (size_t)maxLength[i]);

        uint8_t* fHyphens = (uint8_t*)calloc( params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?11:0) + (params.onlyChar?4:0),sizeof(uint8_t));
        memset(fHyphens, (uint8_t)45, sizeof(uint8_t) * (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)));
        
        wprintf(L"%s%s",fHyphens,hyphens);
        if(col-1 != i) wprintf(L"+--");
        free(hyphens);
    }wprintf(L"\n"RESET);

    for(uint8_t i = 0; i < row; i++){
        wprintf(L"%ls\n"RESET,lines[i]);
    }wprintf(L""RESET);

    for(uint8_t i = 0; i < col; i++){
        uint8_t* hyphens = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
        memset(hyphens, (uint8_t)45, sizeof(uint8_t) * (size_t)maxLength[i]);

        uint8_t* fHyphens = (uint8_t*)calloc( params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?11:0) + (params.onlyChar?4:0),sizeof(uint8_t));
        memset(fHyphens, (uint8_t)45, sizeof(uint8_t) * (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)));
        
        wprintf(L"%s%s",fHyphens,hyphens);
        if(col-1 != i) wprintf(L"+--");
        free(hyphens);
    }wprintf(L"\n"RESET);
}


int main(int argv, char** _args){
    setlocale(LC_ALL, "");
    wchar_t **args = (wchar_t **)calloc(argv,sizeof(wchar_t *));

    for (uint8_t i = 0; i < argv; i++) {
        size_t wide_len = strlen(_args[i]) + 1;
        args[i] = (wchar_t *)calloc( wide_len, sizeof(wchar_t));

        for(uint8_t j = 0; j < wide_len; j++)
        args[i][j] = (wchar_t)_args[i][j];
    }
    
    asciiParams params = parseParameter(argv, args);

    if(params.color){
        system("REG ADD HKCU\\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1");
        return 0;
    }

    uint16_t mem = params.showAll?params.showAll : params.showAllAlphas + params.showAllDigits + params.showSpecialChars + params.showControlChars;
    
    if(mem){
        if(params.content == NULL)
            params.content = (wchar_t*) calloc(params.contentSize, sizeof(wchar_t));
        
        wchar_t* cpy = (wchar_t*) calloc(params.contentSize,sizeof(wchar_t));
        wcscpy(cpy,params.content);

        params.content = (wchar_t*) calloc(mem+params.contentSize+1, sizeof(wchar_t));
        wcscpy(params.content, cpy);
        free(cpy);

        if(params.showAllAlphas || params.showAll){
            wcscat(params.content,L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
            params.contentSize += params.showAllAlphas;
        }

        if(params.showAllDigits|| params.showAll){
            wcscat(params.content,L"0123456789");
            params.contentSize += params.showAllDigits;
        }

        if(params.showSpecialChars || params.showAll){
            wcscat(params.content,L" !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~");
            params.contentSize += params.showSpecialChars;
        }

        if(params.showControlChars  || params.showAll){
            for(uint8_t i = 0; i < 32; i++)
            params.content[ params.contentSize++ ] = (wchar_t)i;
            params.content[ params.contentSize++ ] = (wchar_t)127;
        }
    }

    if(params.content == NULL){
        wprintf(L""YEL"ascii"RESET": No Data Is Found; Output Table Is Empty;");
        return 0;
    }

    if(params.showAll) wprintf(L"ascii - ASCII character set encoded in octal, decimal, and hexadecimal\n");
    
    removeDuplicateChars(&params);
    sortChars(&params);

    HMODULE hDLL = LoadLibrary("renderer.dll");
    if(hDLL == NULL){
        renderTable(params);
        return EXIT_SUCCESS;
    }

    _renderTable __renderTable = (_renderTable)GetProcAddress(hDLL, "_renderTable");
    if (__renderTable == NULL) {
        renderTable(params);
        return EXIT_SUCCESS;
    }

    // renderTable(params);
    __renderTable(params);

    return EXIT_SUCCESS;
}