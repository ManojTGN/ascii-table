#include "renderer.h"

#include <iostream>
#include <iomanip>
#include <stdint.h>

#include <io.h>
#include <fcntl.h>

using namespace std;

enum _BR{
    _HL_1  = L'─',
    _VL_1  = L'│',
    _TLC_1 = L'╭',
    _TRC_1 = L'╮',
    _BLC_1 = L'╰',
    _BRC_1 = L'╯',
    _IL_1  = L'├',
    _IR_1  = L'┤',
    _IC_1  = L'┼',
    _IT_1  = L'┬',
    _IB_1  = L'┴',
    _E     = L' '
};

void _renderTable(asciiParams params){
    // _setmode(_fileno(stdin), _O_U16TEXT);
    // _setmode(_fileno(stdout), _O_U16TEXT);
}
