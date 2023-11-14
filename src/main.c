#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COL 4
#define MAX_ROW 32

typedef struct parameter{

    bool showAll;         //--all  shows all available ascii codes
    bool showAllDigits;   //--digits  shows all digits ascii codes
    bool showAllAlphas;   //--alphas  shows all alphabets ascii codes

    bool onlyOct;      //--octa  shows only octa in output table
    bool onlyDec;      //--dec  shows only dec in output table
    bool onlyHex;      //--hex  shows only hex in output table
    bool onlyChar;     //--char  shows only char in output table
    bool _onlyAll;     // if all only* 4 are false this will be set to true
    
    char* content;     // " " content / data 
    
    uint8_t order;     //0 - default , 1 - ascending, 3 - desending ordered output table

}asciiParams;


void splashScreen(){
    printf("  ascii - ASCII character set encoded in octal, decimal, and hexadecimal\n\n"
           "Oct  Dec Hex Char                         |  Oct  Dec Hex Char  |  Oct  Dec Hex Char |  Oct  Dec Hex Char\n"
           "------------------------------------------+----------------------+----------------------+----------------\n"
           "000   0  00  NUL (null)                   |  000  32  00  SPACE |  000  64  00  @    |  000  96  00  `\n"
           "001   1  01  SOH (start of heading)       |  000  33  00  !     |  000  65  00  A    |  000  97  00  a\n"
           "002   2  02  STX (start of text)          |  000  34  00  \"     |  000  66  00  B    |  000  98  00  b\n"
           "003   3  03  ETX (end of text)            |  000  35  00  #     |  000  67  00  C    |  000  99  00  c\n"
           "004   4  04  EOT (end of transmission)    |  000  36  00  $     |  000  68  00  D    |  000 100  00  d\n"
           "005   5  05  ENQ (enquiry)                |  000  37  00  %%     |  000  69  00  E    |  000 101  00  e\n"
           "006   6  06  ACK (acknowledge)            |  000  38  00  &     |  000  70  00  F    |  000 102  00  f\n"
           "007   7  07  BEL (bell)                   |  000  39  00  '     |  000  71  00  G    |  000 103  00  g\n"
           "008   8  08  BS  (backspace)              |  000  40  00  (     |  000  72  00  H    |  000 104  00  h\n"
           "009   9  09  TAB (horizontal tab)         |  000  41  00  )     |  000  73  00  I    |  000 105  00  i\n"
           "010  10  0A  LF  (NL line feed, new line) |  000  42  00  *     |  000  74  00  J    |  000 106  00  j\n"
           "011  11  0B  VT  (vertical tab)           |  000  43  00  +     |  000  75  00  K    |  000 107  00  k\n"
           "012  12  0C  FF  (NP form feed, new page) |  000  44  00  ,     |  000  76  00  L    |  000 108  00  l\n"
           "013  13  0D  CR  (carriage return)        |  000  45  00  -     |  000  77  00  M    |  000 109  00  m\n"
           "014  14  0E  SO  (shift out)              |  000  46  00  .     |  000  78  00  N    |  000 110  00  n\n"
           "015  15  0F  SI  (shift in)               |  000  47  00  /     |  000  79  00  O    |  000 111  00  o\n"
           "016  16  10  DLE (data link escape)       |  000  48  00  0     |  000  80  00  P    |  000 112  00  p\n"
           "017  17  11  DC1 (device control 1)       |  000  49  00  1     |  000  81  00  Q    |  000 113  00  q\n"
           "018  18  12  DC2 (device control 2)       |  000  50  00  2     |  000  82  00  R    |  000 114  00  r\n"
           "019  19  13  DC3 (device control 3)       |  000  51  00  3     |  000  83  00  S    |  000 115  00  s\n"
           "020  20  14  DC4 (device control 4)       |  000  52  00  4     |  000  84  00  T    |  000 116  00  t\n"
           "021  21  15  NAK (negative acknowledge)   |  000  53  00  5     |  000  85  00  U    |  000 117  00  u\n"
           "022  22  16  SYN (synchronous idle)       |  000  54  00  6     |  000  86  00  V    |  000 118  00  v\n"
           "023  23  17  ETB (end of trans. block)    |  000  55  00  7     |  000  87  00  W    |  000 119  00  w\n"
           "024  24  18  CAN (cancel)                 |  000  56  00  8     |  000  88  00  X    |  000 120  00  x\n"
           "025  25  19  EM  (end of medium)          |  000  57  00  9     |  000  89  00  Y    |  000 121  00  y\n"
           "026  26  1A  SUB (substitute)             |  000  58  00  :     |  000  90  00  Z    |  000 122  00  z\n"
           "027  27  1B  ESC (escape)                 |  000  59  00  ;     |  000  91  00  [    |  000 123  00  {\n"
           "028  28  1C  FS  (file separator)         |  000  60  00  <     |  000  92  00  \\    |  000 124  00  |\n"
           "029  29  1D  GS  (group separator)        |  000  61  00  =     |  000  93  00  ]    |  000 125  00  }\n"
           "030  30  1E  RS  (record separator)       |  000  62  00  >     |  000  94  00  ^    |  000 126  00  ~\n"
           "031  31  1F  US  (unit separator)         |  000  63  00  ?     |  000  95  00  _    |  177 127  00  DEL\n"
           "---------------------------------------------------------------------------------------------------------\n");
}

asciiParams parseParameter(int argv, char** args){
    
    asciiParams params = {0};

    for(uint8_t i = 0; i < argv; i++){
        if     (strcmp(args[i],"--all") == 0)    params.showAll = true;
        else if(strcmp(args[i],"--digits") == 0) params.showAllDigits = true;
        else if(strcmp(args[i],"--alphas") == 0) params.showAllAlphas = true;
        else if(strcmp(args[i],"--octa") == 0) params.onlyOct = true;
        else if(strcmp(args[i],"--dec") == 0) params.onlyDec = true;
        else if(strcmp(args[i],"--hex") == 0) params.onlyHex = true;
        else if(strcmp(args[i],"--char") == 0) params.onlyChar = true;
        else if(strcmp(args[i],"--asc")==0) params.order = 1;
        else if(strcmp(args[i],"--des")==0) params.order = 2;
        else params.content = args[i];
    }

    params._onlyAll = !(params.onlyChar || params.onlyDec || params.onlyHex || params.onlyOct);
    
    return params;

}

void printData(asciiParams params){
    size_t s = 0;
    printf("Oct  Dec Hex Char\n-----------------\n");
    while(strlen(params.content) - s){
        printf("%3o  %3d  %2X  %c\n", params.content[s], params.content[s], params.content[s], params.content[s]);
        s++;
    }
    printf("-----------------\n");
}

int main(int argv, char** args){

    if(argv <= 1){
        splashScreen();
        return 0;
    }

    asciiParams params = parseParameter(argv, args);

    if(params.showAll){
        splashScreen();
        return 0;
    }

    //@todo: print the data first in the center
    //       and then print the table output ..

    // testing params: will be removed on release
    printf("showAll:%i showAllAlphas:%i showAllDigits:%i onlyOct:%i onlyDec:%i onlyHex:%i onlyChar:%i;\ncontent: %s\n\n",params.showAll, params.showAllAlphas, params.showAllDigits, params.onlyOct, params.onlyDec, params.onlyHex, params.onlyChar, params.content);

    printData(params);

    return 0;
}