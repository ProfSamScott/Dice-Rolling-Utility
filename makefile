dice: main.c parser.c parser.h main.h
	gcc -o dice main.c parser.c

test: test.c
	gcc -o test test.c
