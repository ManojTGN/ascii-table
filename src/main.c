#include "ascii.h"

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
                currLineLength = strlen( getPrintable(params.content[s+i]) ) - 3;
                maxLength[currCol-1] = maxLength[currCol-1] < currLineLength?currLineLength:maxLength[currCol-1];
            }
            procCol = currCol;
        }

        snprintf(tmp, sizeof(tmp), "%03o  ", params.content[s]);
        if(params.onlyOct || params._onlyAll) strcat(lines[currRow],tmp);

        snprintf(tmp, sizeof(tmp), "%3d  ", params.content[s]);
        if(params.onlyDec || params._onlyAll) strcat(lines[currRow],tmp);

        snprintf(tmp, sizeof(tmp), " %2X  ", params.content[s]);
        if(params.onlyHex || params._onlyAll) strcat(lines[currRow],tmp);

        if(isPrintable(params.content[s])){
            snprintf(tmp, sizeof(tmp),YEL"%c "RESET, params.content[s]);
            currLineLength = 0;
        }else{
            char* print = getPrintable(params.content[s]);
            currLineLength = strlen(print) - 3;
            snprintf(tmp, sizeof(tmp),YEL"%s"RESET, print);
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

    uint16_t colLineLength = (params.onlyOct || params._onlyAll?5:0) + (params.onlyDec || params._onlyAll?5:0) + (params.onlyHex || params._onlyAll?5:0) + (params.onlyChar || params._onlyAll?5:0);
    
    for(uint8_t i = 0; i < col; i++){
        if(params.onlyOct || params._onlyAll)  printf("Oct  ");
        if(params.onlyDec || params._onlyAll)  printf("Dec  ");
        if(params.onlyHex || params._onlyAll)  printf("Hex  ");
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

        uint8_t* fHyphens = (uint8_t*)calloc( (params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyChar?4:0),sizeof(uint8_t));
        memset(fHyphens, (uint8_t)45, sizeof(uint8_t) * ((params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyChar?4:0)));
        
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

        uint8_t* fHyphens = (uint8_t*)calloc( (params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyChar?4:0),sizeof(uint8_t));
        memset(fHyphens, (uint8_t)45, sizeof(uint8_t) * ((params.onlyDec?5:0) + (params.onlyOct?5:0) + (params.onlyHex?5:0) + (params.onlyChar?4:0)));
        
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

        if(params.showAllAlphas     || params.showAll) strcat(params.content,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        if(params.showAllDigits     || params.showAll) strcat(params.content,"0123456789");
        if(params.showSpecialChars  || params.showAll) strcat(params.content," !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~");
        if(params.showControlChars  || params.showAll){
            char tmp[2];tmp[1] = '\0';
            for(uint8_t i = 0; i < 32; i++){
                tmp[0] = (char)i;
                strcat(params.content, tmp);
            }

            tmp[0] = 127;
            strcat(params.content,tmp);
        }
        
        params.contentSize += mem;
    }

    if(params.content == NULL){
        printf(YEL"ascii"RESET": No Data Is Found; Output Table Is Empty;");
        return 0;
    }

    if(params.showAll) printf("ascii - ASCII character set encoded in octal, decimal, and hexadecimal\n");
    
    removeDuplicateChars(&params);
    sortChars(&params);

    printData(params);

    return 0;
}