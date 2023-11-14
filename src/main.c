#include <stdio.h>


void splashScreen(){
    printf("  ascii - ASCII character set encoded in octal, decimal, and hexadecimal\n"
           "Dec  Char                           Dec  Char     Dec  Char     Dec  Char\n"
           "---------                           ---------     ---------     ----------\n"
           "  0  NUL (null)                      32  SPACE     64  @         96  `\n"
           "  1  SOH (start of heading)          33  !         65  A         97  a\n"
           "  2  STX (start of text)             34  \"         66  B         98  b\n"
           "  3  ETX (end of text)               35  #         67  C         99  c\n"
           "  4  EOT (end of transmission)       36  $         68  D        100  d\n"
           "  5  ENQ (enquiry)                   37  %%         69  E        101  e\n"
           "  6  ACK (acknowledge)               38  &         70  F        102  f\n"
           "  7  BEL (bell)                      39  '         71  G        103  g\n"
           "  8  BS  (backspace)                 40  (         72  H        104  h\n"
           "  9  TAB (horizontal tab)            41  )         73  I        105  i\n"
           " 10  LF  (NL line feed, new line)    42  *         74  J        106  j\n"
           " 11  VT  (vertical tab)              43  +         75  K        107  k\n"
           " 12  FF  (NP form feed, new page)    44  ,         76  L        108  l\n"
           " 13  CR  (carriage return)           45  -         77  M        109  m\n"
           " 14  SO  (shift out)                 46  .         78  N        110  n\n"
           " 15  SI  (shift in)                  47  /         79  O        111  o\n"
           " 16  DLE (data link escape)          48  0         80  P        112  p\n"
           " 17  DC1 (device control 1)          49  1         81  Q        113  q\n"
           " 18  DC2 (device control 2)          50  2         82  R        114  r\n"
           " 19  DC3 (device control 3)          51  3         83  S        115  s\n"
           " 20  DC4 (device control 4)          52  4         84  T        116  t\n"
           " 21  NAK (negative acknowledge)      53  5         85  U        117  u\n"
           " 22  SYN (synchronous idle)          54  6         86  V        118  v\n"
           " 23  ETB (end of trans. block)       55  7         87  W        119  w\n"
           " 24  CAN (cancel)                    56  8         88  X        120  x\n"
           " 25  EM  (end of medium)             57  9         89  Y        121  y\n"
           " 26  SUB (substitute)                58  :         90  Z        122  z\n"
           " 27  ESC (escape)                    59  ;         91  [        123  {\n"
           " 28  FS  (file separator)            60  <         92  \\        124  |\n"
           " 29  GS  (group separator)           61  =         93  ]        125  }\n"
           " 30  RS  (record separator)          62  >         94  ^        126  ~\n"
           " 31  US  (unit separator)            63  ?         95  _        127  DEL\n");
}

int main(int argv, char** args){

    if(argv <= 1){
        splashScreen();
        return 0;
    }




    return 0;
}