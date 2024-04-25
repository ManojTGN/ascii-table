// DLLExample.h
#ifndef _PARTIALS_H_
#define _PARTIALS_H_

#include "table.h"

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) void _renderTable(Table* table);

#ifdef __cplusplus
}
#endif

#endif /*_PARTIALS_H_*/
