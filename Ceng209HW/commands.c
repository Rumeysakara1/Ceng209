// commands.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

//The player checks whether a certain inventor is owned or not
int has_item(Game* game, const char* item_name) {
    printf("Checking inventory for item: %s\n", item_name); // It is for debug.
    for (int i = 0; i < game->player.inventory_count; i++) {
        printf("Inventory item %d: %s\n", i + 1, game->player.inventory[i].name); // Debug mesajı
        if (strcmp(game->player.inventory[i].name, item_name) == 0) {
            printf("Item %s found in inventory.\n", item_name); // It is for debug.
            return 1; // Item found
        }
    }
    printf("Item %s not found in inventory.\n", item_name); // It is for debug.
    return 0; // Item not found
}

// command of move <direction>, with this method, the player will go in the specified direction.
void move(Game* game, char* direction) {
    Room* next_room = NULL;
    if (strcmp(direction, "up") == 0) {
        next_room = game->current_room->up;
    } else if (strcmp(direction, "down") == 0) {
        next_room = game->current_room->down;
    } else if (strcmp(direction, "left") == 0) {
        next_room = game->current_room->left;
    } else if (strcmp(direction, "right") == 0) {
        next_room = game->current_room->right;
    } else {
        printf("Invalid direction: %s\n", direction);
        return;
    }
 if (next_room) {
        // This checks if there is a Toxic Gas Monster in the next room.
        if (strcmp(next_room->description, "5.Toxic Gases Monster Room: The toxic gas monster releases deadly gases, never enter this room without a mask!") == 0) {
            if (!has_item(game, "mask")) {
                printf("You entered the Toxic Gases Monster Room without a mask.\n");
                printf("The toxic gases instantly kill you. You lost the game.\n");
                exit(EXIT_FAILURE);
            } else {
                printf("You have a mask. You safely enter the Toxic Gases Monster Room.\n");
            }
        }
 // This checks the next room for Acid Monster.
        if (strcmp(next_room->description, "7.Acid Monster Room: The strong acid monster is waiting to destroy you, neutralize it with your OH ions in this room and don't forget your anti-corrosion armor!") == 0) {
            int has_mask = has_item(game, "mask");
            int has_oh = has_item(game, "OH");
            int has_armor = has_item(game, "anti_corrosion_armor");

           // Checks whether the player has anticorrosion armor. (The player will protect himself against the Acid Monster with this armor.)
           if (!(has_armor && has_oh)) {
                printf("You entered the Acid Monster Room without both OH ions and anti_corrosion_armor.\n");
                printf("The acid can instantly destroy you. You lost the game.\n");
                exit(EXIT_FAILURE);
            } else {
                printf("You have both OH ions and anti_corrosion_armor. You safely enter the Acid Monster Room.\n");
            }
        }

        // This checks the next room for a Death Beast.
        if (strcmp(next_room->description, "9.Death Monster Room: If you defeat this monster of death, who protects the elixir of immortality at the cost of his life, you will save all humanity!") == 0) {
            printf("You have entered the Death Monster Room. Prepare to face the Death Monster.\n");
        }

        game->current_room = next_room; 

        printf("New Room: %s\n", game->current_room->description);
    } else {
        printf("It is not possible to go in this direction.\n");
    }
}

// command of look, with this method, the player will be able to see the features of the room he is in.  
void look(Game* game) {
    printf("Explanation of Room: %s\n", game->current_room->description);

    if (game->current_room->item_count > 0) {
        printf("Found Items:\n");
        for (int i = 0; i < game->current_room->item_count; i++) {
            printf("- %s (%s)\n", game->current_room->items[i].name, game->current_room->items[i].type);
        }
    } else {
        printf("There is no item in the room.\n");
    }

    if (game->current_room->creature_count > 0) {
        printf("Creatures Encountered:\n");
        for (int i = 0; i < game->current_room->creature_count; i++) {
            printf("- %s (Health: %d, Strength: %d, Type: %s)\n",
                   game->current_room->creatures[i].name,
                   game->current_room->creatures[i].health,
                   game->current_room->creatures[i].strength,
                   game->current_room->creatures[i].type);
        }
    } else {
        printf("There is no creature in the room.\n");
    }
}

// command of inventory, with this method, the player will be able to see the inventories he has.
void inventory(Game* game) {
    printf("Your inventory (%d/%d):\n", game->player.inventory_count, MAX_INVENTORY);
    if (game->player.inventory_count == 0) {
        printf("Your inventory is empty. \n");
    } else {
        for (int i = 0; i < game->player.inventory_count; i++) {
            printf("- %s\n", game->player.inventory[i].name);
        }
    }
}

// command of pickup, with this method, the player will be able to add the items in that room to his inventory. 
void pickup(Game* game, char* item_name) {
    if (game->player.inventory_count >= MAX_INVENTORY) {
        printf("Your inventory is full. Use the inventory command to manage items.\n");
        return;
    }

    int found = -1;
    for (int i = 0; i < game->current_room->item_count; i++) {
        if (strcmp(game->current_room->items[i].name, item_name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("There is no item with this name in the room.\n");
        return;
    }

    // item is added to inventory
    game->player.inventory[game->player.inventory_count++] = game->current_room->items[found];

    // The item taken with the pickup command is removed from the room.
    for (int i = found; i < game->current_room->item_count - 1; i++) {
        game->current_room->items[i] = game->current_room->items[i + 1];
    }
    game->current_room->item_count--;

    printf("%s has been added to your inventory.\n", item_name);
}
//If the player is in the radiation room, before attacking the monster, he will go to the nuclear energy facility,
 //where he will ensure nuclear balance, and will encounter a coded question at the entrance of the facility.

void balance(Game* game) {
    if (strcmp(game->current_room->description, "3.Radiation Monster Room: Go to the nuclear energy facility before the radiation monster wakes up and defeat this monster by maintaining nuclear balance with the 'balance' command!") != 0) {
        printf("There is nothing to balance here.\n");
        return;
    }

    if (game->nuclear_balance) {
        printf("Nuclear balance has already been achieved.\n");
        return;
    }

    // A coded question will be asked
    char answer[100];
    printf("From which element is nuclear energy obtained?\n> ");
    while (1) {
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = 0;

        if (strcmp(answer, "Uranium") == 0 || strcmp(answer, "uranium") == 0) {
            game->nuclear_balance = 1;
            printf("Nuclear balance has been achieved. Radiation has been eliminated! \n");
            break;
        } else {
            printf("Wrong answer. Try again.\n> ");
        }
    }

}
// command of neutralize, If the player enters the acidic room, he will be able to defeat the enemy with the neutralize command with the OH ions he has.
void neutralize(Game* game) {
     printf("Entered neutralize function.\n");
    if (strcmp(game->current_room->description, "7.Acid Monster Room: The strong acid monster is waiting to destroy you, neutralize it with your OH ions in this room and don't forget your anti_corrosion_armor!") != 0) {
        printf("There is nothing to neutralize here.\n");
        return;
    }

    // The player must have both the OH ion and the armor.
    if (has_item(game, "anti_corrosion_armor") && has_item(game, "OH")) {
        Creature* creature = NULL;
        for (int i = 0; i < game->current_room->creature_count; i++) {
            if (strcmp(game->current_room->creatures[i].type, "acid") == 0) {
                creature = &game->current_room->creatures[i];
                break;
            }
        }

         if (creature) {
            printf("You use your anti_corrosion_armor and OH ions to neutralize the Acidic Beast.\n");
            creature->health = 0;
            printf("You have defeated the Acidic Beast!\n");

            for (int i = 0; i < game->current_room->creature_count; i++) {
                if (strcmp(game->current_room->creatures[i].type, "acid") == 0) {
                    for (int j = i; j < game->current_room->creature_count - 1; j++) {
                        game->current_room->creatures[j] = game->current_room->creatures[j + 1];
                    }
                    game->current_room->creature_count--;
                    break;
                }
            }
        } else {
            printf("There is no Acidic Beast to neutralize here.\n");
        }
    } else {
        printf("You need both anti_corrosion_armor and OH ions to neutralize the Acidic Beast.\n");
    }
}

void attack(Game* game) {
    if (game->current_room->creature_count == 0) {
        printf("There are no creatures in the room to attack.\n");
        return;
    }

    
    Creature* creature = &game->current_room->creatures[0];
    printf("Attacking creature: %s\n", creature->name); // Debug message

    // Checks if the player is in the deathbeast room.
    if (strcmp(game->current_room->description, "9.Death Monster Room: If you defeat this monster of death, who protects the elixir of immortality at the cost of his life, you will save all humanity!") == 0 && strcmp(creature->type, "death") == 0) {
        if (game->death_monster_question_solved == 0) {
           //There is a question that must be answered in order to obtain the elixir of immortality hidden by the Death Monster.
            char answer[100];
            printf("Death Monster: Who is the first Turkish scientist to win the Nobel Prize in Chemistry?\n> ");
            while (1) {
                fgets(answer, sizeof(answer), stdin);
                answer[strcspn(answer, "\n")] = 0;
                printf("Player answered: %s\n", answer); // Debug message

                
                if (strcmp(answer, "Aziz Sancar") == 0 || strcmp(answer, "aziz sancar") == 0) { // Doğru cevap
                    game->death_monster_question_solved = 1;
                    printf("The formula for the potion that will defeat the Death Monster was taken from Aziz Sancar. Write the attack command and defeat this monster.\n");
                    break;
                } else {
                    printf("Wrong answer. Try again.\n> ");
                }
            }
            return;
        } else {
            printf("You attack the Death Monster with the elixir formula.\n");
            creature->health = 0;
            printf("You have defeated the Death Monster!\n");
        
            for (int i = 0; i < game->current_room->creature_count - 1; i++) {
                game->current_room->creatures[i] = game->current_room->creatures[i + 1];
            }
            game->current_room->creature_count--;
            printf("You saved all humanity, now everyone is free, everyone was saved with the elixir of immortality!\n");
            return;
        }
    }
// It is handling for Radiation Emitter Monster.
    if (strcmp(creature->type, "radiation") == 0) {
        if (!game->nuclear_balance) {
            printf("You attempt to attack the Radiation Emitters, but without nuclear balance, your attacks are ineffective.\n");
            printf("The Radiation Emitters overpower you. You lost the game.\n");
            exit(EXIT_FAILURE);
        } else {
            printf("With nuclear balance achieved, your attacks are highly effective against the Radiation Emitters!\n");
        }
    }


// It is handling for Toxic Gases Emitter Monster.
    if (strcmp(creature->type, "toxic") == 0) {
        if (!has_item(game, "mask")) {
            printf("You attempt to attack the Toxic Gases Emitters without a mask.\n");
            printf("The toxic gases overwhelm you. You lost the game.\n");
            exit(EXIT_FAILURE);
        } else {
            printf("With a mask equipped, your attacks are effective against the Toxic Gases Emitters!\n");
        }
    }

// It is handling for Acidic Monster.
    if (strcmp(creature->type, "acid") == 0) {
        int has_oh = has_item(game, "OH");
        int has_armor = has_item(game, "anti-corrosion armor");

        if (!has_oh && !has_armor) {
            printf("You attempt to attack the Acidic Beast without OH ions and anti-corrosion armor.\n");
            printf("The acid overwhelms you. You lost the game.\n");
            exit(EXIT_FAILURE);
        }

      int damage_reduction = 0;
        if (has_oh) {
            damage_reduction += 20;
        }

         printf("You attack the Acidic Beast with your current equipment.\n");
        printf("Acidic Beast's strength is reduced by %d.\n", damage_reduction);
        creature->strength -= damage_reduction;
        if (creature->strength < 0) creature->strength = 0;

        printf("The Acidic Beast's strength is now %d.\n", creature->strength);

        if (has_oh) {
            printf("With OH ions and anti_corrosion_armor, your attacks are more effective!\n");
            creature->health -= game->player.strength * 2; // İki kat hasar
        } else {
          
            creature->health -= game->player.strength;
        }
        if (creature->health <= 0) {
            printf("You defeated the Acidic Beast!\n");
        
            for (int i = 0; i < game->current_room->creature_count - 1; i++) {
                game->current_room->creatures[i] = game->current_room->creatures[i + 1];
            }
            game->current_room->creature_count--;
            return;
        }

    
        printf("The Acidic Beast attacks and deals %d damage.\n", creature->strength);
        game->player.health -= creature->strength;
        if (game->player.health <= 0) {
            printf("Your health is depleting. You lost the game.\n");
            exit(EXIT_FAILURE);
        }

        return; 
    }

    printf("The war is starting: %s (Health: %d)\n", creature->name, creature->health);

   
    while (creature->health > 0 && game->player.health > 0) {
       //round-by-round battle between player and monster
        printf("You attack and deal %d damage.\n", game->player.strength);
        creature->health -= game->player.strength;
        if (creature->health <= 0) {
            printf("You defeated %s!\n", creature->name);
            
            for (int i = 0; i < game->current_room->creature_count - 1; i++) {
                game->current_room->creatures[i] = game->current_room->creatures[i + 1];
            }
            game->current_room->creature_count--;
            return;
        }

       
        printf("%s attacks and deals %d damage.\n", creature->name, creature->strength);
        game->player.health -= creature->strength;
        if (game->player.health <= 0) {
            printf("Your health is depleting. You lost the game.\n");
            exit(EXIT_SUCCESS);
        }
    }
}
