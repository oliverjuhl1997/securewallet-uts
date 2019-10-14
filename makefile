#makefile for producing main.out

CC = gcc
CFLAGS = -Wall -ansi -lm

main.out : main_function.o authentication.o encryptionFunction.o search-sort.o decryptionFunction.o header_files.h 
	$(CC) $(CFLAG S) -o main.out main_function.o encryptionFunction.o authentication.o search-sort.o decryptionFunction.o

main_function.o : main_function.c header_files.h
	$(CC) $(CFLAGS) -c -o main_function.o main_function.c

encryptionFunction.o : encryptionFunction.c header_files.h
	$(CC) $(CFLAGS) -c -o encryptionFunction.o encryptionFunction.c

authentication.o : authentication.c header_files.h
	$(CC) $(CFLAGS) -c -o authentication.o authentication.c

search-sort.o : search-sort.c header_files.h
	$(CC) $(CFLAGS) -c -o search-sort.o search-sort.c

decryptionFunction.o : decryptionFunction.c header_files.h
	$(CC) $(CFLAGS) -c -o decryptionFunction.o decryptionFunction.c

clean:
	rm main.out main_function.o authentication.o encryptionFunction.o