#makefile for producing main.out

CC = gcc
CFLAGS = -Wall -ansi -lm
DEBUG = -DDEBUG

main.out : main_function.o encryption.o search-sort.o decryption.o file.o user.o print.o header_files.h
	$(CC) $(CFLAGS) -o main.out main_function.o encryption.o search-sort.o decryption.o file.o user.o print.o

main_function.o : main_function.c header_files.h
	$(CC) $(CFLAGS) -c -o main_function.o main_function.c

encryption.o : encryption.c header_files.h
	$(CC) $(CFLAGS) -c -o encryption.o encryption.c

file.o : file.c header_files.h
	$(CC) $(CFLAGS) -c -o file.o file.c

user.o : user.c header_files.h
	$(CC) $(CFLAGS) -c -o user.o user.c

print.o : print.c header_files.h
	$(CC) $(CFLAGS) -c -o print.o print.c

decryption.o : decryption.c header_files.h
	$(CC) $(CFLAGS) -c -o decryption.o decryption.c

debug: CFLAGS += $(DEBUG)
debug: main_function.o authentication.o encryption.o search-sort.o decryption.o header_files.h
	$(CC) $(CFLAGS) -o main.out main_function.o encryption.o authentication.o search-sort.o decryption.o

clean:
	rm main.out main_function.o authentication.o encryption.o