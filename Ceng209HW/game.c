// game.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

// New room creation function
Room* create_room(const char* description) {
    Room* room = (Room*)malloc(sizeof(Room));
    if (!room) {
        perror("Failed to allocate memory for room");
        exit(EXIT_FAILURE);
    }
    strncpy(room->description, description, MAX_DESCRIPTION);
    room->description[MAX_DESCRIPTION - 1] = '\0';
    room->up = room->down = room->left = room->right = NULL;
    room->item_count = 0;
    room->creature_count = 0;
    return room;
}

// The game is started with this code.
Game* initialize_game() {
    Game* game = (Game*)malloc(sizeof(Game));
    if (!game) {
        perror("Failed to allocate memory for game");
        exit(EXIT_FAILURE);
    }

    // Starting characteristics of the player
    game->player.health = 100;
    game->player.strength = 10;
    game->player.inventory_count = 0;

    // Customization of rooms
    Room* start_room1 = create_room("1.Starting Room: You are at the entrance of your chemistry laboratory.");
    Room* standart_room2 = create_room("2.Standart Room: Various elements and ions are arranged on shelves.[Oxygen, Hydrogen, OH]");
    Room* radiation_room3 = create_room("3.Radiation Monster Room: Go to the nuclear energy facility before the radiation monster wakes up and defeat this monster by maintaining nuclear balance with the 'balance' command!");
    Room* mask_room4 = create_room("4.Chemical Market: You can get the mask item from this market. Get this mask before you encounter the toxic gases monster in room 5!");
    Room* toxic_room5 = create_room("5.Toxic Gases Monster Room: The toxic gas monster releases deadly gases, never enter this room without a mask!");
    Room* armor_room6 = create_room("6.Chemical Market: Get anti-corrosion armor from this market and get rid of your enemies with minimal damage!");
    Room* acid_room7 = create_room("7.Acid Monster Room: The strong acid monster is waiting to destroy you, neutralize it with your OH ions in this room and don't forget your anti-corrosion armor!");
    Room* standart_room8 = create_room("8.Standart Room: Various elements and ions are arranged on shelves. [Oxygen, Hydrogen, OH]");
    Room* death_room9 = create_room("9.Death Monster Room: If you defeat this monster of death, who protects the elixir of immortality at the cost of his life, you will save all humanity!");
    
   

    //Connecting rooms with move <direction>
    start_room1->up = standart_room2;
    start_room1->down = armor_room6;
    start_room1->right =mask_room4;
    start_room1->left = standart_room8;
    
    standart_room2->down = start_room1;
    standart_room2->right =radiation_room3;
    standart_room2->left = death_room9;

    radiation_room3->down = mask_room4;
    radiation_room3->left = standart_room2;

    mask_room4->up = radiation_room3;
    mask_room4->down = toxic_room5;
    mask_room4->left = start_room1;

    toxic_room5->up = mask_room4;
    toxic_room5->left = armor_room6;

    armor_room6->up = start_room1;
    armor_room6->right =toxic_room5;
    armor_room6->left = acid_room7;

    acid_room7->up = standart_room8;
    acid_room7->right =armor_room6;
  

    standart_room8->up = death_room9;
    standart_room8->down = acid_room7;
    standart_room8->right = start_room1;

    death_room9->down = standart_room8;
    death_room9->right = standart_room2;


    // Defining new items
    Item oxygen = {"Oxygen", "element"};
    Item hydrogen = {"Hydrogen", "element"};
    Item oh_ion = {"OH", "ion"}; 
    Item mask = {"mask", "equipment"};
    Item anti_corrosion_armor = {"anti_corrosion_armor", "equipment"};



    //This codes defines which item will be placed in which room.
    standart_room2->items[standart_room2->item_count++] = oxygen;
    standart_room2->items[standart_room2->item_count++] = hydrogen;
    standart_room2->items[standart_room2->item_count++] = oh_ion;
   
    standart_room8->items[standart_room8->item_count++] = oxygen; 
    standart_room8->items[standart_room8->item_count++] = hydrogen;
    standart_room8->items[standart_room8->item_count++] = oh_ion;


    mask_room4->items[mask_room4->item_count++] = mask;

    armor_room6->items[armor_room6->item_count++] = anti_corrosion_armor;

   
    
    //Identification of monsters
    Creature radiation_creature = {"Radiation Emitters",50, 10, "radiation"} ;
    radiation_room3->creatures[radiation_room3->creature_count++] = radiation_creature;

    Creature toxic_gases_creature = {"Toxic Gases Emitters",50, 20, "toxic"} ;
    toxic_room5->creatures[toxic_room5->creature_count++] = toxic_gases_creature;

    Creature acid_creature = {"Acidic Beast", 50, 30, "acid"};
    acid_room7->creatures[acid_room7->creature_count++] = acid_creature;

    Creature death_creature = {"Death Monster", 100, 50, "death"};
    death_room9->creatures[death_room9->creature_count++] = death_creature;


    //It shows which room to start the game from.
    game->current_room = start_room1;  

     game->nuclear_balance = 0;
    game->death_monster_question_solved = 0;
    
    return game;
}

void free_game(Game* game) {
    if (!game) return;

    
    Room* current = game->current_room;
    Room* temp;

    
    while (current->up) {
        temp = current->up;
        free(current);
        current = temp;
    }

    free(current);

    
    free(game);
}
