dice: main.c main.h parser.c parser.h diceio.c diceio.h
	gcc -o dice main.c parser.c diceio.c

histogram: histogram.c
	gcc -o histogram histogram.c

unittests: unittests.c parser.c parser.h diceio.c diceio.h
	gcc -o unittests parser.c diceio.c unittests.c
