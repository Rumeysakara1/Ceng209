// room.h
#ifndef ROOM_H
#define ROOM_H

#include "item.h"

#define MAX_DESCRIPTION 256
#define MAX_ITEMS 5
#define MAX_CREATURES 3

typedef struct Creature {
    char name[50];
    int health;
    int strength;
    char type[20]; 
} Creature;

typedef struct Room {
    char description[MAX_DESCRIPTION];
    struct Room* up;
    struct Room* down;
    struct Room* left;
    struct Room* right;
    int item_count;
    Item items[MAX_ITEMS];
    int creature_count;
    Creature creatures[MAX_CREATURES];
} Room;

#endif 
