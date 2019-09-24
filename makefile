#makefile for producing main.out

main.out : main_function.o gabriel-functions.o
	gcc -Wall -ansi -lm -o main.out main_function.o gabriel-functions.o

main_function.o : main_function.c headerFiles.h
		gcc -Wall -ansi -lm -c -o main_function.o main_function.c

gabriel-functions.o : headerFiles.h
		gcc -Wall -ansi -lm -c -o gabriel-functions.o gabriel-functions.c
		