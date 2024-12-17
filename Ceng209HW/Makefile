# Makefile for Chemistry Maze Adventure

CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = game

SRCS = main.c commands.c game.c load_rooms.c save_load.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c game.h commands.h save_load.h room.h player.h item.h
	$(CC) $(CFLAGS) -c main.c

commands.o: commands.c commands.h game.h room.h player.h item.h
	$(CC) $(CFLAGS) -c commands.c

game.o: game.c game.h room.h player.h item.h
	$(CC) $(CFLAGS) -c game.c

load_rooms.o: load_rooms.c game.h room.h item.h
	$(CC) $(CFLAGS) -c load_rooms.c

save_load.o: save_load.c save_load.h game.h player.h room.h item.h
	$(CC) $(CFLAGS) -c save_load.c


clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean
