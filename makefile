dice: main.c main.h parser.c parser.h diceio.c diceio.h
	gcc -o dice main.c parser.c diceio.c

test: test.c
	gcc -o test test.c
