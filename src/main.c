#include "ascii.h"

void splashScreen(){
    printf("ascii - ASCII character set encoded in octal, decimal, and hexadecimal\n\n"
           "Oct  Dec  Hex  "YEL"Chr"RESET"                          |  Oct  Dec  Hex  "YEL"Chr"RESET"   |  Oct  Dec  Hex  "YEL"Chr"RESET" |  Oct  Dec  Hex  "YEL"Chr"RESET"\n"
           "--------------------------------------------+-----------------------+---------------------+--------------------\n"
           "000    0   00  "YEL"NUL (null)"RESET"                   |  040   32   20  "YEL"SPACE"RESET" |  100   64   40  "YEL"@"RESET"   |  140   96   60  "YEL"`"RESET"\n"
           "001    1   01  "YEL"SOH (start of heading)"RESET"       |  041   33   21  "YEL"!"RESET"     |  101   65   41  "YEL"A"RESET"   |  141   97   61  "YEL"a"RESET"\n"
           "002    2   02  "YEL"STX (start of text)"RESET"          |  042   34   22  "YEL"\""RESET"     |  102   66   42  "YEL"B"RESET"   |  142   98   62  "YEL"b"RESET"\n"
           "003    3   03  "YEL"ETX (end of text)"RESET"            |  043   35   23  "YEL"#"RESET"     |  103   67   43  "YEL"C"RESET"   |  143   99   63  "YEL"c"RESET"\n"
           "004    4   04  "YEL"EOT (end of transmission)"RESET"    |  044   36   24  "YEL"$"RESET"     |  104   68   44  "YEL"D"RESET"   |  144  100   64  "YEL"d"RESET"\n"
           "005    5   05  "YEL"ENQ (enquiry)"RESET"                |  045   37   25  "YEL"%%"RESET"     |  105   69   45  "YEL"E"RESET"   |  145  101   65  "YEL"e"RESET"\n"
           "006    6   06  "YEL"ACK (acknowledge)"RESET"            |  046   38   26  "YEL"&"RESET"     |  106   70   46  "YEL"F"RESET"   |  146  102   66  "YEL"f"RESET"\n"
           "007    7   07  "YEL"BEL (bell)"RESET"                   |  047   39   27  "YEL"'"RESET"     |  107   71   47  "YEL"G"RESET"   |  147  103   67  "YEL"g"RESET"\n"
           "010    8   08  "YEL"BS  (backspace)"RESET"              |  050   40   28  "YEL"("RESET"     |  110   72   48  "YEL"H"RESET"   |  150  104   68  "YEL"h"RESET"\n"
           "011    9   09  "YEL"TAB (horizontal tab)"RESET"         |  051   41   29  "YEL")"RESET"     |  111   73   49  "YEL"I"RESET"   |  151  105   69  "YEL"i"RESET"\n"
           "012   10   0A  "YEL"LF  (NL line feed, new line)"RESET" |  052   42   2A  "YEL"*"RESET"     |  112   74   4A  "YEL"J"RESET"   |  152  106   6A  "YEL"j"RESET"\n"
           "013   11   0B  "YEL"VT  (vertical tab)"RESET"           |  053   43   2B  "YEL"+"RESET"     |  113   75   4B  "YEL"K"RESET"   |  153  107   6B  "YEL"k"RESET"\n"
           "014   12   0C  "YEL"FF  (NP form feed, new page)"RESET" |  054   44   2C  "YEL","RESET"     |  114   76   4C  "YEL"L"RESET"   |  154  108   6C  "YEL"l"RESET"\n"
           "015   13   0D  "YEL"CR  (carriage return)"RESET"        |  055   45   2D  "YEL"-"RESET"     |  115   77   4D  "YEL"M"RESET"   |  155  109   6D  "YEL"m"RESET"\n"
           "016   14   0E  "YEL"SO  (shift out)"RESET"              |  056   46   2E  "YEL"."RESET"     |  116   78   4E  "YEL"N"RESET"   |  156  110   6E  "YEL"n"RESET"\n"
           "017   15   0F  "YEL"SI  (shift in)"RESET"               |  057   47   2F  "YEL"/"RESET"     |  117   79   4F  "YEL"O"RESET"   |  157  111   6F  "YEL"o"RESET"\n"
           "020   16   10  "YEL"DLE (data link escape)"RESET"       |  060   48   30  "YEL"0"RESET"     |  120   80   50  "YEL"P"RESET"   |  160  112   70  "YEL"p"RESET"\n"
           "021   17   11  "YEL"DC1 (device control 1)"RESET"       |  061   49   31  "YEL"1"RESET"     |  121   81   51  "YEL"Q"RESET"   |  161  113   71  "YEL"q"RESET"\n"
           "022   18   12  "YEL"DC2 (device control 2)"RESET"       |  062   50   32  "YEL"2"RESET"     |  122   82   52  "YEL"R"RESET"   |  162  114   72  "YEL"r"RESET"\n"
           "023   19   13  "YEL"DC3 (device control 3)"RESET"       |  063   51   33  "YEL"3"RESET"     |  123   83   53  "YEL"S"RESET"   |  163  115   73  "YEL"s"RESET"\n"
           "024   20   14  "YEL"DC4 (device control 4)"RESET"       |  064   52   34  "YEL"4"RESET"     |  124   84   54  "YEL"T"RESET"   |  164  116   74  "YEL"t"RESET"\n"
           "025   21   15  "YEL"NAK (negative acknowledge)"RESET"   |  065   53   35  "YEL"5"RESET"     |  125   85   55  "YEL"U"RESET"   |  165  117   75  "YEL"u"RESET"\n"
           "026   22   16  "YEL"SYN (synchronous idle)"RESET"       |  066   54   36  "YEL"6"RESET"     |  126   86   56  "YEL"V"RESET"   |  166  118   76  "YEL"v"RESET"\n"
           "027   23   17  "YEL"ETB (end of trans. block)"RESET"    |  067   55   37  "YEL"7"RESET"     |  127   87   57  "YEL"W"RESET"   |  167  119   77  "YEL"w"RESET"\n"
           "030   24   18  "YEL"CAN (cancel)"RESET"                 |  070   56   38  "YEL"8"RESET"     |  130   88   58  "YEL"X"RESET"   |  170  120   78  "YEL"x"RESET"\n"
           "031   25   19  "YEL"EM  (end of medium)"RESET"          |  071   57   39  "YEL"9"RESET"     |  131   89   59  "YEL"Y"RESET"   |  171  121   79  "YEL"y"RESET"\n"
           "032   26   1A  "YEL"SUB (substitute)"RESET"             |  072   58   3A  "YEL":"RESET"     |  132   90   5A  "YEL"Z"RESET"   |  172  122   7A  "YEL"z"RESET"\n"
           "033   27   1B  "YEL"ESC (escape)"RESET"                 |  073   59   3B  "YEL";"RESET"     |  133   91   5B  "YEL"["RESET"   |  173  123   7B  "YEL"{"RESET"\n"
           "034   28   1C  "YEL"FS  (file separator)"RESET"         |  074   60   3C  "YEL"<"RESET"     |  134   92   5C  "YEL"\\"RESET"   |  174  124   7C  "YEL"|"RESET"\n"
           "035   29   1D  "YEL"GS  (group separator)"RESET"        |  075   61   3D  "YEL"="RESET"     |  135   93   5D  "YEL"]"RESET"   |  175  125   7D  "YEL"}"RESET"\n"
           "036   30   1E  "YEL"RS  (record separator)"RESET"       |  076   62   3E  "YEL">"RESET"     |  136   94   5E  "YEL"^"RESET"   |  176  126   7E  "YEL"~"RESET"\n"
           "037   31   1F  "YEL"US  (unit separator)"RESET"         |  077   63   3F  "YEL"?"RESET"     |  137   95   5F  "YEL"_"RESET"   |  177  127   7F  "YEL"DEL"RESET"\n"
           "--------------------------------------------+-----------------------+---------------------+--------------------\n");
}

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
            uint8_t* spaces = (uint8_t*)calloc( (size_t)maxLength[currCol-1] - currLineLength,sizeof(uint8_t));
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
        
        printf("-------------------%s",hyphens);
        if(col-1 != i) printf("+--");
        free(hyphens);
    }printf("\n"RESET);

    for(uint8_t i = 0; i < row; i++){
        printf("%s\n"RESET,lines[i]);
    }printf(RESET);

    for(uint8_t i = 0; i < col; i++){
        uint8_t* hyphens = (uint8_t*)calloc( (size_t)maxLength[i],sizeof(uint8_t));
        memset(hyphens, (uint8_t)45, sizeof(uint8_t) * (size_t)maxLength[i]);
        
        printf("-------------------%s",hyphens);
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
    

    //@todo: print the data first in the center
    //       and then print the table output ..

    if(params.content == NULL){
        printf("ascii: No Data Is Found; Output Table Is Empty;");
        return 0;
    }
    
    removeDuplicateChars(&params);
    sortChars(&params);

    printData(params);

    return 0;
}