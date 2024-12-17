// save_load.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save_load.h"

// This method saves the game.
void save_game(Game* game, const char* filepath) {
    FILE* file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for saving");
        return;
    }

    // This line saves the informations of the player.
    fwrite(&game->player, sizeof(Player), 1, file);

    // This line records the nuclear balance status.
    fwrite(&game->nuclear_balance, sizeof(int), 1, file);

    // This line saves the description of the current room
    fwrite(game->current_room->description, sizeof(char), MAX_DESCRIPTION, file);

    //This saves items in the player's inventory.
    fwrite(&game->player.inventory_count, sizeof(int), 1, file);
    fwrite(game->player.inventory, sizeof(Item), game->player.inventory_count, file);

    fclose(file);
    printf("Game saved: %s\n", filepath);
}

// The function of load the game.
void load_game(Game* game, const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file for loading");
        return;
    }

    //It loads player data.
    fread(&game->player, sizeof(Player), 1, file);

    // It loads the nuclear balance status.
    fread(&game->nuclear_balance, sizeof(int), 1, file);

    // It loads the description of the current room
    char current_room_description[MAX_DESCRIPTION];
    fread(current_room_description, sizeof(char), MAX_DESCRIPTION, file);

    Room* current = game->current_room;
    Room* temp;
    int found = 0;

    //tours the rooms above
    while (current->up) {
        current = current->up;
        if (strcmp(current->description, current_room_description) == 0) {
            game->current_room = current;
            found = 1;
            break;
        }
    }

    //tours the rooms down
    if (!found) {
        current = game->current_room;
        while (current->down) {
            current = current->down;
            if (strcmp(current->description, current_room_description) == 0) {
                game->current_room = current;
                found = 1;
                break;
            }
        }
    }

    // tours the rooms left
    if (!found) {
        current = game->current_room;
        while (current->left) {
            current = current->left;
            if (strcmp(current->description, current_room_description) == 0) {
                game->current_room = current;
                found = 1;
                break;
            }
        }
    }

    // tours the rooms right
    if (!found) {
        current = game->current_room;
        while (current->right) {
            current = current->right;
            if (strcmp(current->description, current_room_description) == 0) {
                game->current_room = current;
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Failed to locate the current room during loading.\n");
    }

    // It loads items in inventory.
    fread(&game->player.inventory_count, sizeof(int), 1, file);
    fread(game->player.inventory, sizeof(Item), game->player.inventory_count, file);

    fclose(file);
    printf("Game loaded: %s\n", filepath);
}
