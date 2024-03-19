dice: main.c main.h parser.c parser.h diceio.c diceio.h
	gcc -o dice main.c parser.c diceio.c

histogram: histogram.c
	gcc -o histogram histogram.c

test: test.c
	gcc -o test test.c
