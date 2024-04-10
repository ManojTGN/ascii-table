#include <assert.h>
#include "ascii.h"

#define OCTAL  8
#define BINARY 2

int main(){

    //YEL RESET
    assert( strcmp(YEL,  "\x1b[33m")== 0 );
    assert( strcmp(RESET,"\x1b[0m" )== 0 );

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
    assert( isBin("")  == false);
    assert( isBin("b") == false);

    return 0;
}
