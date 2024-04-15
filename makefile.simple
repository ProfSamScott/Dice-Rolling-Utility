dice: main.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h 
	gcc -o dice main.c parser.c diceio.c utilities.c

histogram: histogram.c 
	gcc -o histogram histogram.c

expectation: expectation.c 
	gcc -o expectation expectation.c

bin/dice: main.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h
	gcc -o bin/dice main.c parser.c diceio.c utilities.c

bin/histogram: histogram.c
	gcc -o bin/histogram histogram.c

bin/expectation: expectation.c
	gcc -o bin/expectation expectation.c

bin/unittests: unittests.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h
	gcc -o bin/unittests parser.c diceio.c unittests.c utilities.c
