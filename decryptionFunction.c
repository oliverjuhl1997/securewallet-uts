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
		decryption(temp_string, usr);
	}
	else
	{
		return;
	}
}

void decryption(char filename[], user_t** usr)
{
	char encryp_name[MAX_FILENAME_LEN + 3];
	char old_name[MAX_FILENAME_LEN + 1];

	strcpy(encryp_name, filename);
	char name[10];
	strcpy(name, "(en).txt");
	int length;
	length = strlen(name);
	int i;
	for (i=0; i<=strlen(encryp_name); i++)
	{
		if (i == (strlen(encryp_name) - length))
		{
			break;
		}
		else
		{
			old_name[i] = encryp_name[i];
		}
	}
	strcat(old_name, "\0");
	printf("%s\n", old_name);

	FILE *pFILE = NULL;
 	pFILE = fopen(filename, "r");

	if (pFILE == NULL) {
		return;
        printf("Unable to open file\n");
    }

	FILE *newFile = NULL;
    newFile = fopen(filename, "w");

	char currentChar;
	while ((currentChar = getc(pFILE)) != EOF) 
  	{	
 		putc(xor_encryption(currentChar), newFile);
  	}
	printf("%s successfully Decrypted File! New name of file is %s\n", filename, encryp_name);
	deleteNode(usr, filename);
	printf("test\n");
	print_files((*usr)->files);

  	fclose(pFILE);
  	fclose(newFile);
	
	return;
}

void deleteNode(user_t** user, char filename[])
{
	file_t *temp = (*user)->files, *prev;

	if (temp != NULL && (strcmp(temp->filename, filename) == 0))
	{
		printf("Head\n");
		(*user)->files = temp->next;
		free(temp);
		(*user)->files = malloc(sizeof(file_t));
		(*user)->files = NULL;
		(*user)->num_files--;
		printf("Head\n");
		return;
	}
	while (temp != NULL && (strcmp(temp->filename, filename) == 1))
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = temp->next;
	printf("Test\n");
	(*user)->num_files--;
	free(temp);
}