# Chemistry Maze Adventure

Welcome to **Chemistry Maze Adventure**, a captivating text-based adventure game where you navigate through a series of chemistry-themed rooms, collect essential items, and battle formidable monsters to save humanity from impending doom!

## Table of Contents

- [Introduction](#introduction)
- [Gameplay](#gameplay)
  - [Objective](#objective)
  - [Starting Point](#starting-point)
  - [Available Commands](#available-commands)
  - [Key Rooms and Challenges](#key-rooms-and-challenges)
  - [Winning the Game](#winning-the-game)
- [Code Structure](#code-structure)
  - [File Overview](#file-overview)
  - [File Descriptions](#file-descriptions)
- [Game Logic](#game-logic)
  - [Initialization](#initialization)
  - [Player Commands](#player-commands)
  - [Combat Mechanics](#combat-mechanics)
  - [Saving and Loading](#saving-and-loading)
  - [Game Termination](#game-termination)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Steps](#steps)
- [Usage](#usage)
  - [Compiling the Game](#compiling-the-game)
  - [Running the Game](#running-the-game)
  - [Example Session](#example-session)
- [Contributing](#contributing)
- [License](#license)

## Introduction

**Chemistry Maze Adventure** immerses players in a thrilling journey through a chemistry laboratory transformed into a perilous maze. As the protagonist, you must navigate various rooms, each filled with unique challenges, items, and creatures. Your mission is to collect essential items, solve chemistry-related puzzles, and defeat monsters to ultimately save humanity.

## Gameplay

### Objective

Navigate through the chemistry laboratory maze, collect vital items, maintain nuclear balance, and defeat the Death Monster to obtain the elixir of immortality, thereby saving humanity.

### Starting Point

- **Starting Room**: `"1.Starting Room: You are at the entrance of your chemistry laboratory."`

### Available Commands

- **`move <direction>`**: Move the player in the specified direction (`up`, `down`, `left`, `right`).
  
  **Example:**
  ```bash
  move up


look: Provides a detailed description of the current room, including items and creatures present.

inventory: Displays the player's current inventory, showing collected items.

pickup <item>: Adds an item from the current room to the player's inventory.

attack: Engage in combat with creatures present in the room.

balance: Used specifically in the Radiation Monster Room to maintain nuclear balance by answering a chemistry-related question.

neutralize: In the Acid Monster Room, use OH ions and anti-corrosion armor to defeat the Acidic Beast.

save <file path>: Save the current game state to a specified file.

load <file path>: Load a previously saved game state from a specified file.

exit: Exit the game.


Key Rooms and Challenges
Radiation Monster Room (Room 3):

Challenge: Maintain nuclear balance by answering a chemistry-related question.
Command: balance
Toxic Gases Monster Room (Room 5):

Challenge: Requires a mask to survive the toxic gases released by the monster.
Command: move <direction> (with mask equipped)
Acid Monster Room (Room 7):

Challenge: Neutralize the Acidic Beast using OH ions and anti-corrosion armor.
Commands: pickup OH, pickup anti_corrosion_armor, neutralize
Death Monster Room (Room 9):

Challenge: Answer a trivia question to obtain the elixir of immortality and defeat the Death Monster.
Commands: attack (after solving the trivia)
Winning the Game
Defeat the Death Monster in Room 9 by answering the trivia question correctly and using the elixir of immortality to save all humanity. 

Code Structure

Chemistry-Maze-Adventure/
├── Makefile
├── README.md
├── commands.c
├── commands.h
├── game.c
├── game.h
├── item.h
├── load_rooms.c
├── main.c
├── player.h
├── room.h
├── save_load.c
└── save_load.h


File Descriptions
main.c: The entry point of the game. Handles user input, displays the game map, and manages the game loop.

game.c & game.h: Responsible for initializing the game, creating rooms, defining items and creatures, connecting rooms, and managing the game state.

commands.c & commands.h: Implements the core game commands such as move, look, inventory, pickup, attack, balance, and neutralize.

item.h: Defines the Item structure representing items that can be collected by the player.

player.h: Defines the Player structure, including health, strength, and inventory management.

room.h: Defines the Room structure, including descriptions, connected rooms, items, and creatures present in each room.

load_rooms.c: Contains functions to load room data from external files, allowing for dynamic room configurations.

save_load.c & save_load.h: Implements saving and loading game states to and from files, enabling players to continue their adventure from where they left off.

Makefile: Automates the compilation process, defining how to build the project and manage dependencies.

Game Logic
The game operates on a structured logic flow, encompassing player actions, room interactions, and combat mechanics. Here's a breakdown of the core game logic:

Initialization
Game Setup (initialize_game):

Allocates memory for the game state.
Initializes player attributes (health, strength, inventory).
Creates rooms with descriptions.
Connects rooms via directional pointers (up, down, left, right).
Places items and creatures in respective rooms.
Room Connections:

Each room is interconnected to allow movement in four directions.
For example, the Starting Room (Room 1) connects to Standard Room (Room 2) upwards, Armor Room (Room 6) downwards, Mask Room (Room 4) to the right, and Standard Room (Room 8) to the left.
Player Commands
Movement (move):

The player can navigate through the maze by specifying directions.
Movement checks for special conditions in certain rooms, such as needing a mask to enter the Toxic Gases Monster Room.
Inspection (look):

Provides detailed information about the current room, listing available items and creatures.
Helps players strategize their next moves.
Inventory Management (inventory, pickup):

Players can view their collected items and pick up new ones from the room.
Inventory is limited, encouraging strategic item collection.
Combat (attack, neutralize, balance):

Engages players in battles with creatures.
Special commands like balance and neutralize are required to overcome specific challenges, such as maintaining nuclear balance or neutralizing the Acidic Beast.
Combat Mechanics
Standard Attack (attack):

Initiates combat with the first creature in the room.
Players and creatures take turns dealing damage based on their strength attributes.
Combat continues until either the player or the creature is defeated.
Specialized Attacks:

Radiation Creatures: Require nuclear balance to be maintained before attacking.
Toxic Gases Creatures: Require a mask to survive their toxic attacks.
Acidic Beasts: Require OH ions and anti-corrosion armor to neutralize effectively.
Death Monster: Requires answering a trivia question correctly before the final attack.
Saving and Loading
Saving (save_game):

Captures the current game state, including player attributes, inventory, current room, and game-specific flags.
Saves to a specified file path.
Loading (load_game):

Restores the game state from a saved file.
Ensures continuity in the player's adventure.
Game Termination
Winning: Defeating the Death Monster and saving humanity.
Losing: Player's health depletes to zero due to unsuccessful combats or missing required items.


Example Session

    Welcome to the 
Chemistry Maze Adventure!  

* * * * * * * * * * * * * * * * 
*         *         *         *
*    9    *    2    *    3    *
*         *         *         *
* * * * * * * * * * * * * * * *
*         *         *         *
*    8    *    1    *    4    *
*         *         *         *
* * * * * * * * * * * * * * * *
*         *         *         *
*   7     *    6    *    5    *
*         *         *         *
* * * * * * * * * * * * * * * *

1.Starting Room: You are at the entrance of your chemistry laboratory.
2.Standart Room: Various elements and ions are arranged on shelves.[Oxygen, Hydrogen, OH]
3.Radiation Monster Room: Go to the nuclear energy facility before the radiation monster wakes up and defeat this monster by maintaining nuclear balance with the 'balance' command!
4.Chemical Market: You can get the mask item from this market. Get this mask before you encounter the toxic gases monster in room 5!
5.Toxic Gases Monster Room: The toxic gas monster releases deadly gases, never enter this room without a mask!
6.Chemical Market: Get anti-corrosion armor from this market and get rid of your enemies with minimal damage!
7.Acid Monster Room: The strong acid monster is waiting to destroy you, neutralize it with your OH ions in this room and don't forget your anti-corrosion armor!
8.Standart Room: Various elements and ions are arranged on shelves. [Oxygen, Hydrogen, OH]
9.Death Monster Room: If you defeat this monster of death, who protects the elixir of immortality at the cost of his life, you will save all humanity!

Commands:
 move <direction>
 look
 inventory
 pickup <item>
 attack
 save <file path>
 load <file path>
 exit

Enter command: 

