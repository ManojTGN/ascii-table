#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>

#define MAX_COLUMNS 4
#define SHRINK_AT   3

typedef enum col_border {
    LEFT_RIGHT  = 0b0011,
    LEFT        = 0b0010,
    RIGHT       = 0b0001,
    NONE        = 0b0000
} COL_BORDER;


typedef struct row{
    wchar_t* data;
    uint8_t length;

    struct row* _next;
    struct row* _prev;
}Row;

typedef struct table Table;
typedef struct column{
    COL_BORDER border;
    Table* table;

    char* header;
    bool _toShink;
    uint8_t shrinkHeaderSize;
    uint8_t maxHeaderSize;

    uint8_t rowSize;
    uint8_t length;

    Row* head;
    Row*  end;
    Row* _curr;
} Column;

typedef struct table{
    char* header;

    uint8_t maxRows;
    uint16_t length;
    
    uint8_t rowSize;
    uint8_t colSize;

    Column** columns;
} Table;


Row* createRow(wchar_t* data, uint8_t length);

Column* createColumn(char* header, Table* table);
void addRow(Column* column, Row* row);
Row* getRow(Column* column, uint16_t index);

Table* createTable(char* header);
void addColumn(Table* table, Column* column);

void renderTable(Table* table);

#endif /*_TABLE_H_*/