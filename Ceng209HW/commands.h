// commands.h
#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"

void move(Game* game, char* direction);
void look(Game* game);
void inventory(Game* game);
void pickup(Game* game, char* item_name);
void attack(Game* game);
void balance(Game* game);
void neutralize(Game* game); 



#endif 
