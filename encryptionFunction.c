#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

/*******************************************************************************
 * Author: Gabriel
 * This function manages the main function for the options section of the program
 * inputs:
 * - user_t** user: a double pointer containing the address of the user passed
 *					down from the main function
 * outputs: none
*******************************************************************************/
void options_main(user_t** usr)
{
	user_t* user = *usr;
	int choice;
	do
	{
		print_options();
		scanf("%d", &choice);
		auth_option_choice(choice, &user);

	} while (choice != 4);
	printf("You have chosen to log out\n");
}
/*******************************************************************************
 * Author: Gabriel Bogomolets
 * This function allows the user to enter the name of a textfile they wish to 
 * encrypt and call functions to encrypt it.
 * inputs:
 * - user_t** user: a double pointer containing the address of the user passed
 *					down from the main function
 * outputs: none
*******************************************************************************/
void enter_file(user_t** usr)
{
	int counter = 0;
	char filename_temp[MAX_FILENAME_LEN];
	printf("Enter the name of the file you wish to encrypt>\n");
	scanf("%s", filename_temp);
	encrypt_file(filename_temp, usr);
	counter++;
	return;
}

/*******************************************************************************
 * Author: Gabriel Bogomolets
 * This functions searches for the text file and calls a function to encrypt the 
 * file. If successful, the file is added to the linked list. 
 * inputs:
 * - user_t** user: a double pointer containing the address of the user passed
 *					down from the main function
 * - char filename[]: the name of the filename to be encrypted
 * outputs: none
*******************************************************************************/
void encrypt_file(char filename[], user_t** usr)
{
	char encryp_name[MAX_FILENAME_LEN + 3];
	strcpy(encryp_name, filename);
 	strcat(filename, ".txt");
	strcat(encryp_name, "(en).txt");

	FILE *pFILE = NULL;
 	pFILE = fopen(filename, "r");

	if (pFILE == NULL) {
		return;
        printf("Unable to open file\n");
    }
/*	user_t* temp_user = *usr; THIS IS WHAT CAUSED THE ERROR
	temp_user->files = malloc(sizeof(file_t)); */
	int fileSize;

	fileSize = calculcateSize(filename);
	FILE *newFile = NULL;
    newFile = fopen(encryp_name, "w");
	char currentChar;
	while ((currentChar = getc(pFILE)) != EOF) 
  	{	
 		putc(xor_encryption(currentChar), newFile);
  	}
	printf("%s successfully encrypted! New name of file is %s\n", filename, encryp_name);
	if ((*usr)->num_files <= 0)
	{
		(*usr)->files = NULL;
		printf("First file \n");
		(*usr)->files = addHead(encryp_name, fileSize, (*usr)->files);
		(*usr)->num_files = (*usr)->num_files + 1;
	}
	else
	{
		printf("Second file \n");
		(*usr)->files = addFile(encryp_name, fileSize, (*usr)->files);
		(*usr)->num_files++;
	}
	printf("%d\n", (*usr)->num_files);
	printf("Files being printed...\n");
	print_files((*usr)->files);

  	fclose(pFILE);
  	fclose(newFile);

	
	return;
}
/*******************************************************************************
 * Author: Gabriel
 * This function saves the current details of the user to the database textfile 
 * inputs:
 * - char filename[]: The name of the file
 * outputs:
 * - int fileSize: The size of the file in bytes
******************************************************************************/
void saveUser(user_t** usr)
{
	FILE *file1 = NULL;
	FILE *file2 = NULL;
	int lno, count = 0;
	char str[512];
	char temp[] = "temp.txt";

	file1 = fopen(DB_NAME, "r");
	file2 = fopen(temp, "w");

	if (!file2)
	{
		printf("Unable to open file\n");
		fclose(file1);
		return;
	}
	lno = (*usr)->line;
	count = 0;
	while ((fgets(str, 512, file1)) != NULL)
    {
        count++;
     
        if (count == lno)
		{
			fprintf(file2, "%s %s %i", (*usr)->username, (*usr)->pwd, (*usr)->num_files);
			file_t* current = (*usr)->files;
			while (current != NULL)
			{
				fprintf(file2, " %s %d", current->filename, current->size);
				current = current->next;
			}
			fprintf(file2, "\n");
		}    
        else
		{
			fprintf(file2, "%s", str);
		}
            
    }
    fclose(file1);
    fclose(file2);
    remove(DB_NAME);
    rename(temp, DB_NAME); 
    printf(" Replacement did successfully..!! \n");
}


/*******************************************************************************
 * Author: Gabriel
 * This calculates the size of a file.
 * inputs:
 * - char filename[]: The name of the file
 * outputs:
 * - int fileSize: The size of the file in bytes
*******************************************************************************/
int calculcateSize(char filename[])
{
	int size;
	FILE* pFile = fopen(filename, "r");
	fseek(pFile, 0L, SEEK_END);
	size = ftell(pFile);
	fclose(pFile);
	return size;
}

/*******************************************************************************
 * Author: Gabriel
 * This function prints the options user interface for the user
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_options(void)
{
	printf("Select an Option!\n");
	printf(" --------> (1) Display Files\n");
	printf(" --------> (2) Encrypt File\n");
	printf(" --------> (3) Decrypt File\n");
	printf(" --------> (4) Logout\n");
}

/*******************************************************************************
 * Author: Gabriel
 * This function uses a switch statement as a response to user input.
 * Two choices: 1 -> Display Files, 2 -> Encrypt File, 3 -> Decrypt, 4 -> logout.
 * inputs:
 * - int choice: The number used in the switch statement
 * outputs: none
 * - int user_id: an integer value containing the user_id (index) of the user
 * struct that has logged in.  User can either register or login - Allistair
*******************************************************************************/
void auth_option_choice(int choice, user_t** user)
{
	print_files((*user)->files);
	printf("The number of files is %d\n", (*user)->num_files);
	switch (choice)
	{
	case 1:
		printf("Display Files\n");
		break;
	case 2:
		enter_file(user);
		saveUser(user);
		break;
	case 3:
		if ((*user)->num_files == 0)
		{
			printf("No files registered with user %s\n", (*user)->username);
			break;
		}
		decrypt_file(user);
		saveUser(user);
		break;
	case 4:
		choice = 4;
		break;
	default:
		printf("Invalid option!\n");
	}
}

/*******************************************************************************
 * Author: Gabriel Bogomolets
 * This function applies an xor_encryption to a character
 * inputs: 
 * - char pwd: a single character to be encrypted from the text file
 * outputs: 
 * - char: returns the encrypted character
*******************************************************************************/
char xor_encryption(char pwd)
{
  pwd = pwd ^ ENCRYPTION_KEY;
  return pwd;
}

