dice: main.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h
	gcc -o dice main.c parser.c diceio.c utilities.c

histogram: histogram.c
	gcc -o histogram histogram.c

expectation: expectation.c
	gcc -o expectation expectation.c

unittests: unittests.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h
	gcc -o unittests parser.c diceio.c unittests.c utilities.c
