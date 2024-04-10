#include "ascii.h"

uint8_t isHex( char* _hexadecimal ){
    return strlen(_hexadecimal) >= 3 && _hexadecimal[0]=='0' && (_hexadecimal[1]=='x'||_hexadecimal[1]=='X');
}

uint8_t isOct( char* _octal ){
    if(strlen(_octal) <= 1 || _octal[strlen(_octal)-1] != 'o') return 0;
    
    for(uint8_t i = 0; i < strlen(_octal)-1; i++){
        if(!(_octal[i] >= 48 && _octal[i] <= 55)) return 0;
    }

    return 8;
}

uint8_t isBin( char* _binary ){
    if(strlen(_binary) <= 1 || _binary[strlen(_binary)-1] != 'b') return 0;

    for(uint8_t i = 0; i < strlen(_binary)-1; i++){
        if(!(_binary[i] == 48 || _binary[i] == 49)) return 0;
    }

    return 2;
}

uint8_t isDec( char* _decimal ){
    if(strlen(_decimal) <= 1 || _decimal[strlen(_decimal)-1] != 'd') return 0;

    for(uint8_t i = 0; i < strlen(_decimal)-1; i++){
        if(!(_decimal[i] >= 48 && _decimal[i] <= 57)) return 0;
    }

    return 10;
}

asciiParams parseParameter(int argv, char** args){
    asciiParams params = {0};
    if(argv <= 1){
        params.order = 1;
        params.showAll = 128;
    }

    for(uint8_t i = 1; i < argv; i++){

        if(!(strlen(args[i]) >= 2 && args[i][0] == '-' && args[i][1] == '-')){
        
            uint8_t base = 0;
            if( (base = isHex(args[i])) || (base = isOct(args[i])) || (base = isBin( args[i])) || (base = isDec( args[i])) ){
                uint8_t number = (uint8_t) strtol(args[i],NULL,isHex(args[i])?0:base);
                
                free(args[i]);
                args[i] = (uint8_t*) calloc(2,sizeof(uint8_t));

                args[i][0] = number;
                args[i][1] = '\0';
                params.contentSize++;
            }else params.contentSize += strlen(args[i]);


            if(params.content == NULL) params.content = (uint8_t*)args[i];
            else strcat(params.content,(uint8_t*) args[i]);
            
            continue;
        }

        if     (strcmp(args[i],"--all") == 0)    params.showAll = 128;
        else if(strcmp(args[i],"--digits") == 0) params.showAllDigits = 10;
        else if(strcmp(args[i],"--alphas") == 0) params.showAllAlphas = 52;

        else if(strcmp(args[i],"--controls") == 0) params.showControlChars = 33;
        else if(strcmp(args[i],"--specials") == 0) params.showSpecialChars = 33;

        else if(strcmp(args[i],"--oct") == 0) params.onlyOct = true;
        else if(strcmp(args[i],"--dec") == 0) params.onlyDec = true;
        else if(strcmp(args[i],"--hex") == 0) params.onlyHex = true;
        // else if(strcmp(args[i],"--char") == 0) params.onlyChar = true;

        else if(strcmp(args[i],"--asc")==0)  params.order = 1;
        else if(strcmp(args[i],"--desc")==0) params.order = 2;

        else if(strcmp(args[i],"--vt100")==0) params.color = true;

    }

    params.onlyChar = 1; //hardcoded;
    params._onlyAll = !(params.onlyDec || params.onlyHex || params.onlyOct);

    params.content = params.content == NULL?(uint8_t*)calloc(1,sizeof(uint8_t)):params.content;
    // params.contentSize = strlen(params.content);
    
    return params;
}

static int ascCmp(const void* a, const void* b){return *(char *)a > *(char *)b;}
static int desCmp(const void* a, const void* b){return *(char *)a < *(char *)b;}
void removeDuplicateChars(asciiParams *params){
    
    uint8_t occur[256] = {0};int i;int idx = 0;
    for(i = 0; i < params->contentSize; i++){
        if(!occur[params->content[i]]){
            if(idx != i){
                params->content[idx] = params->content[i];
            }

            idx++;
            occur[params->content[i]] = 1;
        }
    }

    uint8_t* tmp = (uint8_t *)calloc(idx ,sizeof(uint8_t));
    params->contentSize = idx;

    strncpy(tmp, params->content, idx);tmp[idx] = '\0';
    params->content = tmp;
}

void sortChars(asciiParams *params){
    if(params->order){
        if(params->order == 1) qsort(params->content, params->contentSize, sizeof(char), ascCmp);
        else qsort(params->content, params->contentSize, sizeof(char), desCmp);
    }
}

bool isPrintable(uint8_t character){
    return !(character >= 0 && character <= 32 || character == 127);
}

uint8_t* getPrintable(uint8_t content){
    if(!(content >= 0 && content <= 32 || content == 127)) return "   ";

    switch (content)
    {
    case 0: return   "NUL (null)";
    case 1: return   "SOH (start of heading)";
    case 2: return   "STX (start of text)";
    case 3: return   "ETX (end of text)";
    case 4: return   "EOT (end of transmission)";
    case 5: return   "ENQ (enquiry)";
    case 6: return   "ACK (acknowledge)";
    case 7: return   "BEL (bell)";
    case 8: return   "BS  (backspace)";
    case 9: return   "TAB (horizontal tab)";
    case 10: return  "LF  (NL line feed, new line)";
    case 11: return  "VT  (vertical tab)";
    case 12: return  "FF  (NP form feed, new page)";
    case 13: return  "CR  (carriage return)";
    case 14: return  "SO  (shift out)";
    case 15: return  "SI  (shift in)";
    case 16: return  "DLE (data link escape)";
    case 17: return  "DC1 (device control 1)";
    case 18: return  "DC2 (device control 2)";
    case 19: return  "DC3 (device control 3)";
    case 20: return  "DC4 (device control 4)";
    case 21: return  "NAK (negative acknowledge)";
    case 22: return  "SYN (synchronous idle)";
    case 23: return  "ETB (end of trans. block)";
    case 24: return  "CAN (cancel)";
    case 25: return  "EM  (end of medium)";
    case 26: return  "SUB (substitute)";
    case 27: return  "ESC (escape)";
    case 28: return  "FS  (file separator)";
    case 29: return  "GS  (group separator)";
    case 30: return  "RS  (record separator)";
    case 31: return  "US  (unit separator)";
    case 32: return  "SPACE";
    case 127:return  "DEL (delete control)";

    default:
        return "   ";
    }
}

