#include <assert.h>
#include "../headers/ascii.h"

#define OCTAL   8
#define BINARY  2
#define DECIMAL 10

int main(){

    //YEL RESET
    assert( strcmp(YEL,   "\x1B[38;5;172m")== 0 );
    assert( strcmp(GRAY,  "\x1B[38;5;243m")== 0 );
    assert( strcmp(RESET, "\x1b[0m")== 0 );

    // isHex()
    assert( isHex("0x00") == true );
    assert( isHex("0x01") == true );
    assert( isHex("0x127")== true );
    assert( isHex("0x255")== true );
    assert( isHex("0x256")== true );
    assert( isHex("")     == false);
    assert( isHex("x0")   == false);
    assert( isHex("x0x")  == false);
    assert( isHex("x0x")  == false);
    assert( isHex("x0x0") == false);
    assert( isHex("xx0")  == false);
    assert( isHex("0x")   == false);
    assert( isHex("00x")  == false);
    assert( isHex("1x0")  == false);
    assert( isHex("00x1") == false);

    // isOct()
    assert( isOct("1o") == OCTAL);
    assert( isOct("2o") == OCTAL);
    assert( isOct("3o") == OCTAL);
    assert( isOct("4o") == OCTAL);
    assert( isOct("5o") == OCTAL);
    assert( isOct("6o") == OCTAL);
    assert( isOct("7o") == OCTAL);
    assert( isOct("17o")== OCTAL);
    assert( isOct("27o")== OCTAL);
    assert( isOct("")   == false);
    assert( isOct("o")  == false);
    assert( isOct("8o") == false);
    assert( isOct("9o") == false);
    assert( isOct("19o")== false);
    assert( isOct("29o")== false);
    assert( isOct("1")  == false);
    assert( isOct("2")  == false);
    assert( isOct("3")  == false);
    assert( isOct("4")  == false);
    assert( isOct("5")  == false);
    assert( isOct("6")  == false);
    assert( isOct("7")  == false);
    assert( isOct("8")  == false);

    // isBin()
    assert( isBin("")       == false );
    assert( isBin("b")      == false );
    assert( isBin("2b")     == false );
    assert( isBin("3b")     == false );
    assert( isBin("4b")     == false );
    assert( isBin("5b")     == false );
    assert( isBin("6b")     == false );
    assert( isBin("7b")     == false );
    assert( isBin("8b")     == false );
    assert( isBin("9b")     == false );
    assert( isBin("0b")     == BINARY);
    assert( isBin("1b")     == BINARY);
    assert( isBin("10001b") == BINARY);

    //isDec()
    assert( isDec("0")      == false  );
    assert( isDec("100")    == false  );
    assert( isDec("999")    == false  );
    assert( isDec("6969")   == false  );
    assert( isDec("010")    == false  );
    assert( isDec("0d")     == DECIMAL);
    assert( isDec("10d")    == DECIMAL);
    assert( isDec("100d")   == DECIMAL);

    return 0;
}
