// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

#define MAX_INVENTORY 10

typedef struct {
    int health;
    int strength;
    int inventory_count;
    Item inventory[MAX_INVENTORY];
} Player;

#endif 
