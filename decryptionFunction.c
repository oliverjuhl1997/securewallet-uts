#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"


void decrypt_file(user_t** usr)
{
	char filename_temp[MAX_FILENAME_LEN];
	char temp_string[MAX_FILENAME_LEN + 3];

	printf("Enter the name of the file you wish to decrypt>\n");
	scanf("%s", filename_temp);
	strcpy(temp_string, filename_temp);
	strcat(temp_string, "(en).txt");

	int true = 0;
	file_t *current = (*usr)->files;
	while (current != NULL)
	{
		if (strcmp(temp_string, current->filename) == 0)
		{
			printf("The file exists\n");
			true = 1;
			break;
		}
		current = current->next;
	}
	if (true == 1)
	{
		decryption(temp_string, filename_temp, usr);
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
		return;
        printf("Unable to open file\n");
    }

	FILE *newFile = NULL;
    newFile = fopen(newfile, "w");

	char currentChar;
	while ((currentChar = getc(pFILE)) != EOF) 
  	{	
 		putc(xor_encryption(currentChar), newFile);
  	}
	printf("%s successfully Decrypted File! New name of file is %s\n", filename, newfile);
	printf("%s\n", filename);
	
	printf("The number of files is %d\n", (*usr)->num_files);
	head = removeNode(head, (*usr)->num_files, filename);
	print_files(head);
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
			printf("File found\n");
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


