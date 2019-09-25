#makefile for producing main.out

CC = gcc
CFLAGS = -Wall -ansi -lm

main.out : main_function.o gabriel-functions.o
	$(CC) $(CFLAGS) -o main.out main_function.o gabriel-functions.o

main_function.o : main_function.c headerFiles.h
		$(CC) $(CFLAGS) -c -o main_function.o main_function.c

gabriel-functions.o : gabriel-functions.c headerFiles.h
		$(CC) $(CFLAGS) -c -o gabriel-functions.o gabriel-functions.c
		
clean:
	rm main.out main_function.o gabriel-functions.o