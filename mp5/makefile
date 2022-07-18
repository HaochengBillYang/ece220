all:
	gcc -Wall -g -I include/ -L lib/ main.c updateBoard.c -o gameoflife -lncurses
	gcc -Wall -g test.c updateBoard.c updateBoardGold.o -o test
clean:
	rm gameoflife
	rm test
