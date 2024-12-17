// load_rooms.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define MAX_LINE 256

Room* load_room(FILE* file) {
    char line[MAX_LINE];
    if (!fgets(line, sizeof(line), file)) return NULL;

    Room* room = create_room(line);

    // Eşya sayısını oku
    if (!fgets(line, sizeof(line), file)) return room;
    int item_count = atoi(line);
    for (int i = 0; i < item_count; i++) {
        if (!fgets(line, sizeof(line), file)) break;
        char name[50], type[20];
        sscanf(line, "%s %s", name, type);
        Item item;
        strcpy(item.name, name);
        strcpy(item.type, type);
        room->items[room->item_count++] = item;
    }

    // Yaratık sayısını oku
    if (!fgets(line, sizeof(line), file)) return room;
    int creature_count = atoi(line);
    for (int i = 0; i < creature_count; i++) {
        if (!fgets(line, sizeof(line), file)) break;
        char name[50], type[20];
        int health, strength;
        sscanf(line, "%s %d %d %s", name, &health, &strength, type);
        Creature creature;
        strcpy(creature.name, name);
        creature.health = health;
        creature.strength = strength;
        strcpy(creature.type, type);
        room->creatures[room->creature_count++] = creature;
    }

    return room;
}

void load_rooms(Game* game, const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("Failed to open rooms file");
        return;
    }

    
    Room* previous_room = NULL;
    Room* first_room = NULL;

    while (!feof(file)) {
        Room* room = load_room(file);
        if (!room) break;

        if (!first_room) {
            first_room = room;
        }

        if (previous_room) {
           
            previous_room->up = room;
            room->down = previous_room;
        }

        previous_room = room;
    }

    game->current_room = first_room;

    fclose(file);
}
