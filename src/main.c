#include "ascii.h"
#include "table.h"

typedef void (*_renderTable)(Table* table);

/**
 * @brief printing the content into table format
 * 
 * @param params 
 */
void printData(asciiParams params){
    uint8_t col = (params.contentSize%MAX_ROW) == 0?(params.contentSize/MAX_ROW):(params.contentSize/MAX_ROW)+1;
    uint8_t row = col > 1?MAX_ROW:params.contentSize;
    
    uint8_t* maxLength = (uint8_t*) calloc(col,sizeof(uint8_t));
    char** lines = (char**)calloc(row,sizeof(char*));
    size_t s = 0;

    for(uint8_t i = 0; i < row; i++)
        lines[i] = (char*)calloc(300,sizeof(char));

    uint8_t currRow = s%row;
    uint8_t currCol = (s/row)+1;
    uint8_t procCol = 0;
    uint8_t currLineLength = 0;
    while(params.contentSize - s){
        char tmp[60];
        currRow = s%row;
        currCol = (s/row)+1;

        if(currCol != procCol){
            for(uint8_t i = 0; i < row && s+i < params.contentSize; i++){
                currLineLength = wcslen( getPrintable(params.content[s+i]) ) - 3;
                maxLength[currCol-1] = maxLength[currCol-1] < currLineLength?currLineLength:maxLength[currCol-1];
            }
            procCol = currCol;
        }

        if(s%2 == 0){
            strcat(lines[currRow],GRAY);
        }

        if(params.onlyOct || params._onlyAll){
            snprintf(tmp, sizeof(tmp), "%03o  ", params.content[s]);
            strcat(lines[currRow],tmp);
        }

        if(params.onlyDec || params._onlyAll){
            snprintf(tmp, sizeof(tmp), "%3d  ", params.content[s]);
            strcat(lines[currRow],tmp);
        }

        if(params.onlyHex || params._onlyAll){
            snprintf(tmp, sizeof(tmp), " %2X  ", params.content[s]);
            strcat(lines[currRow],tmp);
        }

        if(params.onlyBin /*|| params._onlyAll*/){
            uint8_t index = 0; uint8_t content = params.content[s];
            uint8_t binStr[10] = "0000 0000\0";

            for(uint8_t i = 128; i > 0 && content != 0; ){
                if(binStr[index] == ' '){
                    index++;
                    continue;
                }

                if(content >= i){
                    binStr[index] = '1';
                    content -= i;
                }

                index++;
                i=(i/2);
            }
            
            snprintf(tmp, sizeof(tmp), "%s  ",  binStr);
            strcat(lines[currRow],tmp);
        }

        if(isPrintable(params.content[s])){
            snprintf(tmp, sizeof(tmp),s%2==0?YEL"%c "RESET:GOLD"%c "RESET, params.content[s]);
            currLineLength = 0;
        }else{
            wchar_t* print = getPrintable(params.content[s]);
            currLineLength = wcslen(print) - 3;
            snprintf(tmp, sizeof(tmp),s%2==0?YEL"%s"RESET:GOLD"%s"RESET, print);
        }
        if(params.onlyChar || params._onlyAll) strcat(lines[currRow],tmp);

        if(currCol != col){
            uint8_t* spaces = (uint8_t*)calloc( (size_t)maxLength[currCol-1] - currLineLength +1,sizeof(uint8_t));
            memset(spaces, (uint8_t)32, sizeof(uint8_t) * (size_t)maxLength[currCol-1] - currLineLength);

            strcat(lines[currRow],spaces);
            strcat(lines[currRow],currLineLength == 0?"  |  ":" |  ");

            free(spaces);
        }
        s++;
    }

    uint16_t colLineLength = (params.onlyOct || params._onlyAll?5:0) + (params.onlyDec || params._onlyAll?5:0) + (params.onlyHex || params._onlyAll?5:0) + (params.onlyBin /*|| params._onlyAll*/?11:0) + (params.onlyChar || params._onlyAll?5:0);
    
    for(uint8_t i = 0; i < col; i++){
        if(params.onlyOct || params._onlyAll)  printf("Oct  ");
        if(params.onlyDec || params._onlyAll)  printf("Dec  ");
        if(params.onlyHex || params._onlyAll)  printf("Hex  ");
        if(params.onlyBin /*|| params._onlyAll*/)  printf("Binary     ");
        if(params.onlyChar|| params._onlyAll)  printf(YEL"Chr"RESET);

        if(col != i+1){
            uint8_t* spaces = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
            memset(spaces, (uint8_t)32, sizeof(uint8_t) * (size_t)maxLength[i]);

            printf(" %s|  ",spaces);
            free(spaces);
        }
    }printf("\n"RESET);

    for(uint8_t i = 0; i < col; i++){
        uint8_t* hyphens = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
        memset(hyphens, (uint8_t)45, sizeof(uint8_t) * (size_t)maxLength[i]);

        uint8_t* fHyphens = (uint8_t*)calloc( params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?11:0) + (params.onlyChar?4:0),sizeof(uint8_t));
        memset(fHyphens, (uint8_t)45, sizeof(uint8_t) * (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)));
        
        printf("%s%s",fHyphens,hyphens);
        if(col-1 != i) printf("+--");
        free(hyphens);
    }printf("\n"RESET);

    for(uint8_t i = 0; i < row; i++){
        printf("%s\n"RESET,lines[i]);
    }printf(RESET);

    for(uint8_t i = 0; i < col; i++){
        uint8_t* hyphens = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
        memset(hyphens, (uint8_t)45, sizeof(uint8_t) * (size_t)maxLength[i]);

        uint8_t* fHyphens = (uint8_t*)calloc( params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?11:0) + (params.onlyChar?4:0),sizeof(uint8_t));
        memset(fHyphens, (uint8_t)45, sizeof(uint8_t) * (params._onlyAll?(params.onlyBin?19+11:19):(params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyBin?10:0) + (params.onlyChar?4:0)));
        
        printf("%s%s",fHyphens,hyphens);
        if(col-1 != i) printf("+--");
        free(hyphens);
    }printf("\n"RESET);

}


int main(int argv, char** args){

    asciiParams params = parseParameter(argv, args);
    
    if(params.color){
        system("REG ADD HKCU\\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1");
        return 0;
    }
    
    uint16_t mem = params.showAll?params.showAll : params.showAllAlphas + params.showAllDigits + params.showSpecialChars + params.showControlChars;
    
    if(mem){
        if(params.content == NULL)
            params.content = (uint8_t*) calloc(params.contentSize, sizeof(uint8_t));
        
        uint8_t* cpy = (uint8_t*) calloc(params.contentSize,sizeof(uint8_t));
        strcpy(cpy,params.content);

        params.content = (uint8_t*) calloc(mem+params.contentSize+1, sizeof(uint8_t));
        strcat(params.content, cpy);
        free(cpy);

        if(params.showAllAlphas || params.showAll){
            strcat(params.content,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
            params.contentSize += params.showAllAlphas;
        }

        if(params.showAllDigits|| params.showAll){
            strcat(params.content,"0123456789");
            params.contentSize += params.showAllDigits;
        }

        if(params.showSpecialChars || params.showAll){
            strcat(params.content," !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~");
            params.contentSize += params.showSpecialChars;
        }

        if(params.showControlChars  || params.showAll){
            for(uint8_t i = 0; i < 32; i++)
            params.content[ params.contentSize++ ] = (uint8_t)i;
            params.content[ params.contentSize++ ] = (uint8_t)127;
        }
    }

    if(params.content == NULL){
        printf(YEL"ascii"RESET": No Data Is Found; Output Table Is Empty;");
        return 0;
    }

    if(params.showAll) printf("ascii - ASCII character set encoded in octal, decimal, and hexadecimal\n");
    
    removeDuplicateChars(&params);
    sortChars(&params);
    
    // printData(params);

    HMODULE hDLL = LoadLibrary("table.dll");
    if(hDLL == NULL){
        fprintf(stderr,"Failed To Load DLL");
        return EXIT_FAILURE;
    }

    _renderTable __renderTable = (_renderTable)GetProcAddress(hDLL, "_renderTable");
    if (__renderTable == NULL) {
        printf("Failed to get function address");
        return EXIT_FAILURE;
    }

    Table* outputTable = createTable("AsciiTable");
    outputTable->maxRows = 32;

    Column* octalColumn = createColumn("Octal", outputTable);
    Column* decimalColumn = createColumn("Decimal", outputTable);
    Column* hexaColumn = createColumn("HexaDecimal", outputTable);
    Column* charColumn = createColumn("Character", outputTable);

    octalColumn->shrinkHeaderSize = decimalColumn->shrinkHeaderSize = hexaColumn->shrinkHeaderSize = 3;
    charColumn->shrinkHeaderSize = 4;

    wchar_t _tmp[60] = {0};
    Row* _tmpRow;

    for(uint8_t i = 0; i < params.contentSize; i++){
        snwprintf(_tmp, sizeof(_tmp), L"%03o", params.content[i]);
        _tmpRow = createRow(_tmp, 0);
        addRow(octalColumn,_tmpRow);
        
        snwprintf(_tmp, sizeof(_tmp), L"%3d", params.content[i]);
        _tmpRow = createRow(_tmp, 0);
        addRow(decimalColumn,_tmpRow);

        snwprintf(_tmp, sizeof(_tmp), L"%2X", params.content[i]);
        _tmpRow = createRow(_tmp, 0);
        addRow(hexaColumn,_tmpRow);
        
        if(isPrintable(params.content[i])){
            snwprintf(_tmp, sizeof(_tmp),L"%c"RESET, params.content[i]);
            _tmpRow = createRow(_tmp, 1);
        }else{
            wchar_t* print = getPrintable(params.content[i]);
            _tmpRow = createRow(print, 0);
        }

        addRow(charColumn,_tmpRow);
    }

    if( params.onlyOct || params._onlyAll) addColumn(outputTable, octalColumn);
    if( params.onlyDec || params._onlyAll) addColumn(outputTable, decimalColumn);
    if( params.onlyHex || params._onlyAll) addColumn(outputTable, hexaColumn);
    if( params.onlyChar|| params._onlyAll) addColumn(outputTable, charColumn);

    // renderTable(outputTable);
    __renderTable(outputTable);

    return EXIT_SUCCESS;
}