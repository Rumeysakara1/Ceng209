// save_load.h
#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "game.h"

void save_game(Game* game, const char* filepath);
void load_game(Game* game, const char* filepath);

#endif 
