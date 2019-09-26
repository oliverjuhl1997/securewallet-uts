#makefile for producing main.out

CC = gcc
CFLAGS = -Wall -ansi -lm

main.out : main_function.o authentication.o
	$(CC) $(CFLAGS) -o main.out main_function.o authentication.o

main_function.o : main_function.c headerFiles.h
	$(CC) $(CFLAGS) -c -o main_function.o main_function.c

authentication.o : authentication.c headerFiles.h
	$(CC) $(CFLAGS) -c -o authentication.o authentication.c

clean:
	rm main.out main_function.o authentication.o