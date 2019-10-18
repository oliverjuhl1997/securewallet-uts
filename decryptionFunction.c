#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"


void decrypt_file(user_t** usr)
{
	char temp_string[MAX_FILENAME_LEN + 3];
	char buffer[1000];
	char filename[1000];
	int valid = 0;
	int checkOnce = 1;

	while (valid == 0)
	{
		printf("Enter the name of the original file you wish to decrypt>\n");
		checkOnce = removeNewLine(checkOnce);

		/* Gets the input using fgets and then checks if an empty
        line is entered */
		char *pointer = buffer;
		fgets(buffer, 4096, stdin);

		if (sscanf(buffer, "%s", filename) == -1)
		{
			printf("Invalid empty line\n");
			continue;
		}
		/* Checks for spaces in the line */
		if ((pointer = strpbrk(pointer, " ")))
		{
			printf("No spaces allowed\n");
			continue;
		}
		/*Check length of string */
		if ((strlen(filename) >= 1) && (strlen(filename) <= MAX_FILENAME_LEN))
		{
			valid = 1;
		}
	}
	strcpy(temp_string, filename);
	strcat(temp_string, "(en).txt");

	int true = 0;
	file_t *current = (*usr)->files;
	while (current != NULL)
	{
		if (strcmp(temp_string, current->filename) == 0)
		{
			true = 1;
			break;
		}
		current = current->next;
	}
	if (true == 1)
	{
		decryption(temp_string, filename, usr);
	}
	else
	{
		return;
	}
}

void decryption(char filename[], char newfile[], user_t** usr)
{
	strcat(newfile, ".txt");
	FILE *pFILE = NULL;
	file_t* head = (*usr)->files;

 	pFILE = fopen(filename, "r");

	if (pFILE == NULL) {
	    printf("Unable to open file\n");
		return;
    }

	FILE *newFile = NULL;
    newFile = fopen(newfile, "w");

	char currentChar;

#ifdef DEBUG
	printf("DEBUG ---- Applying XOR Decryption\n");
	printf("\n");
#endif

	while ((currentChar = getc(pFILE)) != EOF) 
  	{	
		putc(xor_dencryption(currentChar), newFile);
  	}
	printf("%s successfully Decrypted File! New name of file is %s\n", filename, newfile);
	remove(filename);
	printf("Deleted %s....\n", filename);
	
	head = removeNode(head, (*usr)->num_files, filename);
	(*usr)->files = head;
	(*usr)->num_files = (*usr)->num_files - 1;
	

  	fclose(pFILE);
  	fclose(newFile);
	
	return;
}
file_t* removeNode(file_t* head, int files, char filename[])
{
	if (files <= 1)
	{
		head = head->next;
		head = NULL;
		return head;
	}
	else
	{
		/* The head of the linked list */
		if (strcmp(head->filename, filename) == 0)
		{
#ifdef DEBUG
			printf("DEBUG ---- Head to be removed\n");
#endif
			file_t* temp = head;
			head = head -> next;
			free(temp);
			return head;
		}
		else
		{
			file_t* current = head->next;
			file_t* previous = head;
			while (current != NULL && previous != NULL)
			{
				if (strcmp(filename, current->filename) == 0)
				{
#ifdef DEBUG
					printf("DEBUG ---- Removing file from linked list\n");
#endif
					file_t* temp = current;
					previous->next = current->next;
					free(temp);
					return head;
				}
				previous = current;
				current = current->next;
			}
			return head;
		}
	}
	return head;
}	


