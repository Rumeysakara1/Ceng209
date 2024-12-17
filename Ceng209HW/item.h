// item.h
#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM_NAME 50
#define MAX_ITEM_TYPE 20

typedef struct {
    char name[MAX_ITEM_NAME];
    char type[MAX_ITEM_TYPE]; 
} Item;

#endif 
