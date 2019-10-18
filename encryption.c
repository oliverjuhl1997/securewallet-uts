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
		user_option_choice(choice, &user);

	} while (choice != 4);
	printf("You have chosen to log out\n");
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
	int file_size;

	file_size = calculcate_size(filename);
	FILE *new_file = NULL;
    new_file = fopen(encryp_name, "w");
	char current_char;
	while ((current_char = getc(pFILE)) != EOF)
  	{
 		putc(xor_encryption_char(current_char), new_file);
  	}
	printf("%s successfully encrypted! New name of file is %s\n", filename, encryp_name);
	if ((*usr)->num_files <= 0)
	{
		(*usr)->files = NULL;
		printf("First file \n");
		(*usr)->files = add_head(encryp_name, file_size, (*usr)->files);
		(*usr)->num_files = (*usr)->num_files + 1;
	}
	else
	{
		printf("Second file \n");
		(*usr)->files = add_file(encryp_name, file_size, (*usr)->files);
		(*usr)->num_files++;
	}
	printf("%d\n", (*usr)->num_files);
	printf("Files being printed...\n");
	print_files((*usr)->files);

  	fclose(pFILE);
  	fclose(new_file);


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
void save_user(user_t** usr)
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
int calculcate_size(char filename[])
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
 * This function uses a switch statement as a response to user input.
 * Two choices: 1 -> Display Files, 2 -> Encrypt File, 3 -> Decrypt, 4 -> logout.
 * inputs:
 * - int choice: The number used in the switch statement
 * outputs: none
 * - int user_id: an integer value containing the user_id (index) of the user
 * struct that has logged in.  User can either register or login - Allistair
*******************************************************************************/
void user_option_choice(int choice, user_t** user)
{
	print_files((*user)->files);
	printf("The number of files is %d\n", (*user)->num_files);
	switch (choice)
	{
	case 1:
		file_options((*user)->files);
		break;
	case 2:
		enter_file(user);
		save_user(user);
		break;
	case 3:
		if ((*user)->num_files == 0)
		{
			printf("No files registered with user %s\n", (*user)->username);
			break;
		}
		decrypt_file(user);
		save_user(user);
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
char xor_encryption_char(char pwd)
{
  pwd = pwd ^ ENCRYPTION_KEY;
  return pwd;
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function both encrypts and decrypts the password of the user. This is
 * done by using the XOR encryption algorithm.
 *
 * Explanation line 58 -> pwd[counter] ^ encr_key[counter % ENCRYPTION_KEY_LEN]:
 * This line of code uses the exclusive OR operator "^" to compare bits of the
 * characters in the password with the characters in the encryption key.
 *
 * Example of encrypting "oliver":
 * First, we convert "oliver" and the encryption key into binary, since is used
 * for the comparison of the XOR operator.
 * o -> 01101111        0 -> 00110000
 * l -> 01101100        x -> 01111000
 * i -> 01101001        F -> 01000110
 * v -> 01110110        A -> 01000001
 * e -> 01100101        C -> 01000011
 * r -> 01110010        A -> 01000001
 * The compare them using the XOR operator:
 * 01101111 ^ 00110000 = 01011111
 * 01101100 ^ 01111000 = 00010100
 * 01101001 ^ 01000110 = 00101111
 * 01110110 ^ 01000001 = 00110111
 * 01100101 ^ 01000011 = 00100110
 * 01110010 ^ 01000001 = 00110011
 *
 * Encrypted password: 01011111 00010100 00101111 00110111 00100110 00110011
 * Translated: _/7&3
 *
 * inputs:
 * - char pwd[]: a string containing the password for the user
*******************************************************************************/
void xor_encryption(char pwd[])
{
  /* First we convert our encryption key from int to char array */
  char encr_key[ENCRYPTION_KEY_LEN];
  sprintf(encr_key, "%i", ENCRYPTION_KEY);

  int counter;
  for (counter = 0; counter < strlen(pwd); counter++)
  {
    /* Exclusive OR operation to generate new encryption password */
    pwd[counter] = pwd[counter] ^ encr_key[counter % ENCRYPTION_KEY_LEN];
  }
}
