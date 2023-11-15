#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_COL 4
#define MAX_ROW 32
#define YEL     "\x1b[33m"
#define RESET   "\x1b[0m"

typedef struct parameter{

    bool showAll;           //--all  shows all available ascii codes
    bool showAllDigits;     //--digits  shows all digits ascii codes
    bool showAllAlphas;     //--alphas  shows all alphabets ascii codes

    bool onlyOct;           //--octa  shows only octa in output table
    bool onlyDec;           //--dec  shows only dec in output table
    bool onlyHex;           //--hex  shows only hex in output table

    bool onlyChar;          // hardcoded and set to true(1) always shows `chr` column
    bool _onlyAll;          // if all only* 3 are false this will be set to true
    
    char* content;          // " " content / data (user input)
    
    uint8_t order;          //0 - default , (--asc)1 - ascending, (--des)2 - desending ordered output table
    bool color;             //--vt100 register ansi vt100 escape sequence color to the terminal

}asciiParams;


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
           "---------------------------------------------------------------------------------------------------------------\n");
}

asciiParams parseParameter(int argv, char** args){
    
    asciiParams params = {0};

    for(uint8_t i = 1; i < argv; i++){

        if(!(strlen(args[i]) >= 2 && args[i][0] == '-' && args[i][1] == '-')){
            if(params.content == NULL) params.content = args[i];
            else strcat(params.content, args[i]);

            continue;
        }

        if     (strcmp(args[i],"--all") == 0)    params.showAll = true;
        else if(strcmp(args[i],"--digits") == 0) params.showAllDigits = true;
        else if(strcmp(args[i],"--alphas") == 0) params.showAllAlphas = true;

        else if(strcmp(args[i],"--octa") == 0) params.onlyOct = true;
        else if(strcmp(args[i],"--dec") == 0) params.onlyDec = true;
        else if(strcmp(args[i],"--hex") == 0) params.onlyHex = true;
        // else if(strcmp(args[i],"--char") == 0) params.onlyChar = true;

        else if(strcmp(args[i],"--asc")==0) params.order = 1;
        else if(strcmp(args[i],"--des")==0) params.order = 2;

        else if(strcmp(args[i],"--vt100")==0) params.color = true;

    }

    params.onlyChar = 1; //hardcoded;
    params._onlyAll = !(params.onlyDec || params.onlyHex || params.onlyOct);
    
    return params;

}

static int ascCmp(const void* a, const void* b){return *(char *)a > *(char *)b;}
static int desCmp(const void* a, const void* b){return *(char *)a < *(char *)b;}
void manipulateData(asciiParams *params){

    char occur[256] = {0};int i;int idx = 0;

    for(i = 0; i < strlen(params->content); i++){
        if(!occur[params->content[i]]){
            if(idx != i){
                params->content[idx] = params->content[i];
            }

            idx++;
            occur[params->content[i]] = 1;
        }
    }
    
    char* tmp = (char *)malloc((idx) * sizeof(char));
    strncpy(tmp, params->content, idx);tmp[idx] = '\0';
    params->content = tmp;

    if(params->order){
        if(params->order == 1) qsort(params->content, strlen(params->content), sizeof(char), ascCmp);
        else qsort(params->content, strlen(params->content), sizeof(char), desCmp);
    }
}

void printData(asciiParams params){

    size_t s = 0;char se_line[20] = "";
    if(params._onlyAll) printf("Oct  Dec  Hex  "YEL"Chr"RESET"\n------------------\n");
    else{
        if(params.onlyOct){  printf("Oct  "); strcat(se_line,"-----");}
        if(params.onlyDec){  printf("Dec  "); strcat(se_line,"-----");}
        if(params.onlyHex){  printf("Hex  "); strcat(se_line,"-----");}
        if(params.onlyChar){ printf(YEL"Chr"RESET); strcat(se_line,"---");}
        printf("\n%s\n",se_line);
    }

    while(strlen(params.content) - s){
        if(params._onlyAll) printf("%3o  %3d   %2X  "YEL"%c"RESET"\n", params.content[s], params.content[s], params.content[s], params.content[s]);
        else{
            if(params.onlyOct)  printf("%3o  ", params.content[s]);
            if(params.onlyDec)  printf("%3d  ", params.content[s]);
            if(params.onlyHex)  printf(" %2X  ", params.content[s]);
            if(params.onlyChar) printf(YEL"%c"RESET, params.content[s]);
            printf("\n");
        }
        s++;
    }

    if(params._onlyAll) printf("------------------\n");
    else printf("%s",se_line);
}


int main(int argv, char** args){

    if(argv <= 1){
        splashScreen();
        return 0;
    }

    asciiParams params = parseParameter(argv, args);

    if(params.color){
        system("REG ADD HKCU\\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1");
        return 0;
    }

    if(params.showAll){
        splashScreen();
        return 0;
    }else if(params.showAllAlphas && params.showAllDigits){
        params.content = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    }else if(params.showAllAlphas){
        params.content = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    }else if(params.showAllDigits){
        params.content = "0123456789";
    }

    //@todo: print the data first in the center
    //       and then print the table output ..

    if(params.content == NULL){
        printf("ascii: No Data Is Found; Output Table Is Empty;");
        return 0;
    }

    manipulateData(&params);
    printData(params);

    return 0;
}