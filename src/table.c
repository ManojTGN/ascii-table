#include "table.h"

Table* createTable(char* header){
    Table* table = (Table*) calloc(1, sizeof(Table));
    if(table == NULL) return NULL;

    table->header = header;
    table->columns = (Column**) calloc(MAX_COLUMNS, sizeof(Column*));
    return table;
}

void renderTable(Table* table){
    char* borderLine = (char*) calloc(table->length+1, sizeof(char));
    memset(borderLine, '-', table->length);

    printf("%s\n",borderLine);
    for(uint8_t j = 0; j < table->rowSize; j++){
    for(uint8_t i = 0; i < table->colSize; i++){
        if(table->columns[i]->_curr == NULL) continue;
        printf("%s ",table->columns[i]->_curr->data);
        table->columns[i]->_curr = table->columns[i]->_curr->_next;
    }printf("\n");
    }

    printf("%s\n",borderLine);
}


Column* createColumn(char* header, Table* table){
    Column* column = (Column*) calloc(1, sizeof(Column));
    if(column == NULL) return NULL;

    column->table = table;
    column->header = header;
    column->maxHeaderSize = strlen(header);

    column->border = NONE;
    // table->columns[table->colSize++] = column;
    return column;
}

void addColumn(Table* table, Column* column){
    table->columns[table->colSize++] = column;
    table->length += column->length;

    if(!column->_toShink && column->table->maxRows != 0)
    column->_toShink = (column->rowSize/table->maxRows) >= SHRINK_AT;

    switch (column->border){
        case LEFT_RIGHT:{
            if( table->colSize - 2 >= 0 &&
                (table->columns[table->colSize - 2]->border == RIGHT || 
                table->columns[table->colSize - 2]->border == LEFT_RIGHT)
            ) table->length += 3; else table->length += 4;
            break;
        }
        case LEFT:case RIGHT:{
            if( table->colSize - 2 >= 0 && column->border == LEFT &&
                (table->columns[table->colSize - 2]->border == RIGHT || 
                table->columns[table->colSize - 2]->border == LEFT_RIGHT)
            ) table->length += 2;
            else if( table->colSize - 2 >= 0 && column->border == RIGHT &&
                (table->columns[table->colSize - 2]->border == RIGHT || 
                table->columns[table->colSize - 2]->border == LEFT_RIGHT)
            ) table->length += 3; else table->length += 2;

            break;
        }
        case NONE:{
            if( table->colSize - 2 >= 0 && 
                (table->columns[table->colSize - 2]->border == RIGHT || 
                table->columns[table->colSize - 2]->border == LEFT_RIGHT)
            ) table->length += 2; else table->length += 1;
            break;
        }
        default:break;
    }
}


Row* createRow(wchar_t* data, uint8_t length){
    Row* row = (Row*) calloc(1, sizeof(Row));
    if(row == NULL) return NULL;

    row->length = (length == 0)?wcslen(data):length;
    
    row->data = (wchar_t*) calloc(length+1,sizeof(wchar_t));
    // strcpy(row->data, data);
    wcscpy(row->data,data);

    row->_next = row->_prev = NULL;
    return row;
}

void addRow(Column* column, Row* row){
    column->rowSize++;
    if(column->table->rowSize < column->rowSize) column->table->rowSize = column->rowSize;

    if(row->length > column->length) column->length = row->length;
    
    if(!column->_toShink && column->table->maxRows != 0)
    column->_toShink = (column->rowSize/column->table->maxRows) >= SHRINK_AT;

    if(column->head == NULL){
        column->head = column->end = column->_curr = row;
        return;
    }
    
    row->_prev = column->end;
    column->end->_next = row;
    column->end = column->end->_next;
}

Row* getRow(Column* column, uint16_t index){
    Row* tmp = column->head;
    if(tmp == NULL) return NULL;

    for(uint16_t i = 0; i < index; i++) tmp = tmp->_next;

    return tmp;
}
