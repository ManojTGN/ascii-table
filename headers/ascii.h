#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifndef _ASCII_H_
#define _ASCII_H_

#define MAX_COL 4
#define MAX_ROW 32
#define YEL     "\x1b[33m"
#define RESET   "\x1b[0m"

typedef struct parameter{
    uint8_t showAll;        //--all  shows all available ascii codes
    uint8_t showAllDigits;  //--digits  shows all digits ascii codes
    uint8_t showAllAlphas;  //--alphas  shows all alphabets ascii codes

    uint8_t showControlChars;//--controls shows all control ascii codes
    uint8_t showSpecialChars;//--specials shows all special ascii codes

    bool onlyOct;           //--oct  shows only octa in output table
    bool onlyDec;           //--dec  shows only dec in output table
    bool onlyHex;           //--hex  shows only hex in output table

    bool onlyChar;          // hardcoded and set to true(1) always shows `chr` column
    bool _onlyAll;          // if all only* 3 are false this will be set to true
    
    uint8_t* content;       // " " content / data (user input)
    uint16_t contentSize;   // content size 
    
    uint8_t order;          //0 - default , (--asc)1 - ascending, (--des)2 - desending ordered output table
    bool color;             //--vt100 register ansi vt100 escape sequence color to the terminal
}asciiParams;

uint8_t isHex( char* _hexadecimal );
uint8_t isOct( char* _octal );
uint8_t isBin( char* _binary );
uint8_t isDec( char* _decimal );

asciiParams parseParameter(int argv, char** args);
void removeDuplicateChars(asciiParams *params);
void sortChars(asciiParams *params);

bool isPrintable(uint8_t character);
uint8_t* getPrintable(uint8_t content);

static int ascCmp(const void* a, const void* b);
static int desCmp(const void* a, const void* b);

#endif /* _ASCII_H_ */
