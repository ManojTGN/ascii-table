#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>

#define MAX_ROWS    32
#define MAX_COLUMNS 4

typedef struct row{
    wchar_t* data;
    uint8_t length;

    struct row* _next;
    struct row* _prev;
}Row;

typedef struct table Table;
typedef struct column{
    Table* table;

    wchar_t* title;
    uint8_t titleLength;

    uint8_t rowSize;
    uint8_t totalLength[4];

    Row* head;
    Row*  end;
    Row* _curr;
} Column;

typedef struct table{
    wchar_t* title;

    uint8_t colSize;
    uint8_t rowSize;
    uint8_t maxRows;
    
    uint16_t totalLength;

    Column** columns;
} Table;

Row* createRow(wchar_t* data, uint8_t length);

Column* createColumn(wchar_t* title, Table* table);
void addRow(Column* column, Row* row);

Table* createTable(wchar_t* title);
void addColumn(Table* table, Column* column);

void renderTable(Table* table);

#endif /*_TABLE_H_*/