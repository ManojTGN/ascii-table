#include "ascii.h"

/**
 * @brief check wheather the given string is hexadecimal &
 *        returns 1 if it is hexadecimal else 0
 * 
 * @param _hexadecimal char* (string)
 * @return uint8_t 
 */
uint8_t isHex( wchar_t* _hexadecimal ){
    return wcslen(_hexadecimal) >= 3 && _hexadecimal[0]==L'0' && (_hexadecimal[1]==L'x'||_hexadecimal[1]==L'X');
}

/**
 * @brief check wheather the given string is octal &
 *        returns 8(OCTAL BASE) if it is octal else 0
 * 
 * @param _octal char* (string)
 * @return uint8_t 
 */
uint8_t isOct( wchar_t* _octal ){
    if(wcslen(_octal) <= 1 || _octal[wcslen(_octal)-1] != L'o') return 0;
    
    for(uint8_t i = 0; i < wcslen(_octal)-1; i++){
        if(!(_octal[i] >= 48 && _octal[i] <= 55)) return 0;
    }

    return 8;
}

/**
 * @brief check wheather the given string is binary &
 *        returns 2(BINARY BASE) if it is binary else 0
 * 
 * @param _binary char* (string)
 * @return uint8_t 
 */
uint8_t isBin( wchar_t* _binary ){
    if(wcslen(_binary) <= 1 || _binary[wcslen(_binary)-1] != L'b') return 0;

    for(uint8_t i = 0; i < wcslen(_binary)-1; i++){
        if(!(_binary[i] == 48 || _binary[i] == 49)) return 0;
    }

    return 2;
}

/**
 * @brief check wheather the given string is decimal &
 *        returns 10(DECIMAL BASE) if it is decimal else 0
 * 
 * @param _binary char* (string)
 * @return uint8_t 
 */
uint8_t isDec( wchar_t* _decimal ){
    if(wcslen(_decimal) <= 1 || _decimal[wcslen(_decimal)-1] != L'd') return 0;

    for(uint8_t i = 0; i < wcslen(_decimal)-1; i++){
        if(!(_decimal[i] >= 48 && _decimal[i] <= 57)) return 0;
    }

    return 10;
}

/**
 * @brief Parse the arguments & makes process to the asciiParams
 *        according to the arguments and returns the asciiParams
 * 
 * @param argv int
 * @param args char** (string[])
 * @return asciiParams 
 */
asciiParams parseParameter(int argv, wchar_t** args){
    asciiParams params = {0};
    if(argv <= 1){
        params.order = 1;
        params.showAll = 128;
    }

    for(uint8_t i = 1; i < argv; i++){

        if(!(wcslen(args[i]) >= 2 && args[i][0] == L'-' && args[i][1] == L'-')){
        
            uint8_t base = 0;
            if( (base = isHex(args[i])) || (base = isOct(args[i])) || (base = isBin( args[i])) || (base = isDec( args[i])) ){
                wchar_t number = (wchar_t) wcstol(args[i],NULL,isHex(args[i])?0:base);
                
                free(args[i]);
                args[i] = (wchar_t*) calloc(2,sizeof(wchar_t));

                args[i][0] = number;
                args[i][1] = L'\0';
                params.contentSize++;
            }else params.contentSize += wcslen(args[i]);

            if(params.content == NULL) params.content = (wchar_t*)args[i];
            else wcscat(params.content,(wchar_t*) args[i]);

            continue;
        }

        if     (wcscmp(args[i],L"--all") == 0)    params.showAll = 128;
        else if(wcscmp(args[i],L"--digits") == 0) params.showAllDigits = 10;
        else if(wcscmp(args[i],L"--alphas") == 0) params.showAllAlphas = 52;

        else if(wcscmp(args[i],L"--controls") == 0) params.showControlChars = 33;
        else if(wcscmp(args[i],L"--specials") == 0) params.showSpecialChars = 33;

        else if(wcscmp(args[i],L"--octa") == 0) params.onlyOct = true;
        else if(wcscmp(args[i],L"--dec") == 0) params.onlyDec = true;
        else if(wcscmp(args[i],L"--hex") == 0) params.onlyHex = true;
        else if(wcscmp(args[i],L"--bin") == 0) params.onlyBin = true;
        // else if(wcscmp(args[i],L"--char") == 0) params.onlyChar = true;

        else if(wcscmp(args[i],L"--asc")==0)  params.order = 1;
        else if(wcscmp(args[i],L"--desc")==0) params.order = 2;

        else if(wcscmp(args[i],L"--vt100")==0) params.color = true;
    }

    params.onlyChar = 1; //hardcoded;
    params._onlyAll = !(params.onlyDec || params.onlyHex || params.onlyOct);

    if(params.showAll && params.order == 0) params.order = 1;
    if(params.showAll){
        params.showAllAlphas = 52;
        params.showAllDigits = 10;
        params.showControlChars = 33;
        params.showSpecialChars = 33;
    }
    
    return params;
}

/**
 * @brief remove dupilicate characters in the input content &
 *        changes the size of the input content (contentSize)
 * 
 * @param params asciiParams*
 */
void removeDuplicateChars(asciiParams *params){
    wchar_t occur[256] = {0};int i;int idx = 0;

    for(i = 0; i < params->contentSize; i++){
        if(!occur[params->content[i]]){

            if(idx != i){
                params->content[idx] = params->content[i];
            }

            idx++;
            occur[params->content[i]] = 1;
        }
    }

    if(idx == params->contentSize) return;

    wchar_t* tmp = (wchar_t *)calloc(idx ,sizeof(wchar_t));
    params->contentSize = idx;

    wcsncpy(tmp, params->content, idx);tmp[idx] = '\0';
    // free(params->content);
    params->content = tmp;
}

static int ascCmp(const void* a, const void* b){return *(wchar_t *)a - *(wchar_t *)b;}
static int desCmp(const void* a, const void* b){return *(wchar_t *)b - *(wchar_t *)a;}

/**
 * @brief sort the input content in ascending / descending order
 *        according to the order input specified with `--asc`/`--desc`
 * 
 * @param params asciiParams*
 */
void sortChars(asciiParams *params){
    if(params->order){
        if(params->order == 1) qsort(params->content, params->contentSize, sizeof(wchar_t), ascCmp);
        else qsort(params->content, params->contentSize, sizeof(wchar_t), desCmp);
    }
}

/**
 * @brief checks wheather the character is printable on the screen
 *        or not and if printable it returns true else false
 * 
 * @param character 
 * @return bool 
 */
bool isPrintable(wchar_t character){
    return !(character >= 0 && character <= 32 || character == 127);
}

/**
 * @brief Get the printable custom value for non printable characters
 * 
 * @param content 
 * @return wchar_t* 
 */
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

