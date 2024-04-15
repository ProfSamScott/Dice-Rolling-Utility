##########################
# used during development
##########################

# link rule
dice: obj/main.o obj/parser.o obj/diceio.o obj/utilities.o  
	gcc -o dice obj/main.o obj/parser.o obj/diceio.o obj/utilities.o

# compile rules
obj/main.o: main.c utilities.h parser.h diceio.h
	mkdir -p obj
	gcc -c main.c -o obj/main.o

obj/parser.o: parser.c parser.h utilities.h
	mkdir -p obj
	gcc -c parser.c -o obj/parser.o

obj/diceio.o: diceio.c diceio.h utilities.h parser.h
	mkdir -p obj
	gcc -c diceio.c -o obj/diceio.o

obj/utilities.o: utilities.c utilities.h
	mkdir -p obj
	gcc -c utilities.c -o obj/utilities.o

# link and compile rules
histogram: histogram.c 
	gcc -o histogram histogram.c

expectation: expectation.c 
	gcc -o expectation expectation.c

#######################################
# used in workflows (link and compile)
#######################################
bin/dice: main.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h
	gcc -o bin/dice main.c parser.c diceio.c utilities.c

bin/histogram: histogram.c
	gcc -o bin/histogram histogram.c

bin/expectation: expectation.c
	gcc -o bin/expectation expectation.c

bin/unittests: unittests.c parser.c parser.h diceio.c diceio.h utilities.c utilities.h
	gcc -o bin/unittests parser.c diceio.c unittests.c utilities.c
