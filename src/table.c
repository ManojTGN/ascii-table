#include "table.h"

Table* createTable(wchar_t* title){
    Table* table = (Table*) calloc(1, sizeof(Table));
    if(table == NULL) return NULL;

    table->title = title;
    table->columns = (Column**) calloc(MAX_COLUMNS, sizeof(Column*));
    return table;
}

void renderTable(Table* table){
/*
 * @todo
 * rewrite: render the table without the extended ascii / utf16
 */
}


Column* createColumn(wchar_t* title, Table* table){
    Column* column = (Column*) calloc(1, sizeof(Column));
    if(column == NULL) return NULL;

    column->table = table;
    column->title = title;
    column->titleLength = wcslen(title);
    // column->totalLength[0] = column->titleLength;

    // table->columns[table->colSize++] = column;
    return column;
}

void addColumn(Table* table, Column* column){
    table->columns[table->colSize++] = column;

    for(uint8_t i = 0; i < MAX_COLUMNS; i++){
        table->totalLength += column->totalLength[i];
    }

    if(column->rowSize > table->rowSize) table->rowSize = column->rowSize;
}


Row* createRow(wchar_t* data, uint8_t length){
    Row* row = (Row*) calloc(1, sizeof(Row));
    if(row == NULL) return NULL;

    row->length = (length == 0)?wcslen(data):length;
    
    row->data = (wchar_t*) calloc(row->length+1,sizeof(wchar_t));
    wcscpy(row->data,data); 
    
    row->_next = row->_prev = NULL;
    return row;
}

void addRow(Column* column, Row* row){

    if(row->length > column->totalLength[column->rowSize/MAX_ROWS]) column->totalLength[column->rowSize/MAX_ROWS] = row->length;
    
    column->rowSize++;
    // column->table->rowSize++;

    if(column->head == NULL){
        column->head = column->end = column->_curr = row;
        return;
    }
    
    row->_prev = column->end;
    column->end->_next = row;
    column->end = column->end->_next;
}
