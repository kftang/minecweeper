CC=gcc
CFLAGS=-g -lncurses

minecweeper: minecweeper.c input.o game.o graphics.o 
	$(CC) -o minecweeper minecweeper.c input.o graphics.o game.o $(CFLAGS)

input.o: input.c
	$(CC) -c -o input.o input.c $(CFLAGS)

game.o: game.c
	$(CC) -c -o game.o game.c $(CFLAGS)

graphics.o: graphics.c
	$(CC) -c -o graphics.o graphics.c $(CFLAGS)
