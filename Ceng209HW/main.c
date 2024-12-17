// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "commands.h"
#include "save_load.h"

#define MAX_INPUT 100

int main() {
    Game* game = initialize_game();
    char input[MAX_INPUT];
    char command[20];
    char argument[80];
    
    #include <stdio.h>

    FILE *file;
    char map[500];

    // Open the file in read mode
    file = fopen("map.txt", "r");
    if (file == NULL) {
        perror("The file could not be opened.");
        return EXIT_FAILURE;
    }

    // Reading and printing line by line to the end of the file
    while (fgets(map, sizeof(map), file) != NULL) {
        printf("%s", map);
    }

    // close the file
    fclose(file);

    


    printf("Commands:\n move <direction>\n look\n inventory\n pickup <item>\n attack\n save <file path>\n load <file path>\n exit\n");

     while (1) {
        printf("\nEnter command: ");
        fgets(input, sizeof(input), stdin);

      
        input[strcspn(input, "\n")] = 0;

        // Parse command and argument
        if (sscanf(input, "%s %s", command, argument) < 1) {
            continue;
        }

        if (strcmp(command, "move") == 0) {
            if (sscanf(input, "%s %s", command, argument) == 2) {
                move(game, argument);
            } else {
                printf("Usage: move <direction>\n");
            }
        } else if (strcmp(command, "look") == 0) {
            look(game);
        } else if (strcmp(command, "inventory") == 0) {
            inventory(game);
        } else if (strcmp(command, "pickup") == 0) {
            if (sscanf(input, "%s %s", command, argument) == 2) {
                pickup(game, argument);
            } else {
                printf("Usage: pickup <item>\n");
            }
        } else if (strcmp(command, "attack") == 0) {
            attack(game);

        }else if (strcmp(command, "neutralize") == 0) {
             printf("Calling neutralize function...\n");
            neutralize(game);
         
        } else if (strcmp(command, "balance") == 0) {
            balance(game);
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting game. Goodbye!\n");
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }
    //This frees memory. 
    free_game(game);
    return 0;
}
