// game.h
#ifndef GAME_H
#define GAME_H

#define MAX_DESCRIPTION 256
#define MAX_ITEMS 10
#define MAX_CREATURES 10
#define MAX_INVENTORY 10

// attributes of item 
typedef struct Item {
    char name[50];
    char type[50];
} Item;

// attributes of creature
typedef struct Creature {
    char name[50];
    int health;
    int strength;
    char type[50];
} Creature;

// attributes of room
typedef struct Room {
    char description[MAX_DESCRIPTION];
    struct Room* up;
    struct Room* down;
    struct Room* left;
    struct Room* right;
    struct Item items[MAX_ITEMS];
    int item_count;
    struct Creature creatures[MAX_CREATURES];
    int creature_count;
} Room;

// attributes of player
typedef struct Player {
    int health;
    int strength;
    Item inventory[MAX_INVENTORY];
    int inventory_count;
} Player;

// attributes of game
typedef struct Game {
    Room* current_room;
    Player player;
    int nuclear_balance;
    int death_monster_question_solved; 
} Game;

Game* initialize_game();
void free_game(Game* game);

#endif 
