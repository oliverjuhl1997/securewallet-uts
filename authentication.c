#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

/*******************************************************************************
 * Author: Alistair Coomber
 * This function uses a switch statement as a response to user input.
 * Two choices: 1 -> register, 2 -> login
 * inputs:
 * - int choice: The number used in the switch statement
 * outputs: none
 * - int user_id: an integer value containing the user_id (index) of the user
 * struct that has logged in.  User can either register or login - Allistair
*******************************************************************************/
void auth_choice(int choice, user_t** user)
{
	switch (choice)
	{
	case 1:
		login(user);
		break;
	case 2:
		register_user();
		break;
	case 3:
		exit(0);
	default:
		user = NULL;
		printf("Invalid option!\n");
	}
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function adds the registered user information into a new structure
 * of type user by firstly dynamically allocating memory and then storing the
 * users information
 * inputs:
 * - char username[]: a string containing the username for the user
 * - char password[]: a string containing the password for the user
*******************************************************************************/
void register_user(void)
{
	user_t user;

	printf("Enter usename: ");
	scanf("%s", user.username);
	printf("Enter password: ");
	scanf("%s", user.pwd);

	user.files = NULL;
	FILE *file = NULL;

	file = fopen(DB_NAME, "a");
	if (file == NULL)
	{
		printf("Unable to open file at path: %s\n", DB_NAME);
	}
	if (calculcateSize(DB_NAME) == 0)
	{
		fprintf(file, "%s %s %i", user.username, user.pwd, 0);
	}
	else
	{
		fprintf(file, "\n%s %s %i", user.username, user.pwd, 0);
	}
	
	fclose(file);
	printf("Successfully registered user\n\n");
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function loads the user details from an external text file database and
 * saves them into an array of user structures.
 * Furthermore, it loads the files with filename and size into a linked list.
 * inputs:
 * - char username[]: Username entered through the terminal
 * - char pwd[]: Password entered through the terminal
 * - char *files: Pointer to the head of the linked list of files to fill out
 * outputs:
 * - int: 1 if user exists and matches the input else 0
*******************************************************************************/
int find_user(char username[], char pwd[], user_t** user)
{
	FILE *file = NULL;
	file = fopen(DB_NAME, "r");
	int line = 0;
	if (file == NULL)
	{
		printf("Unable to open file at path: %s\n", DB_NAME);
		return 0;
	}
	char line_in_file[512];
	
	while (fgets(line_in_file, 512, file))
	{
		/*
		user_t* temp_user = *user; 
		(*user)->files = malloc(sizeof(file_t)); */

		(*user) = malloc(sizeof(user_t));
		(*user)->files = malloc(sizeof(file_t));
		char temp_username[MAX_USERNAME_LEN + 1];
		char temp_pwd[MAX_PWD_LEN + 1];
		int num_of_files = 0;
		int counter = 1;
		line++;
		char *part_of_line = strtok(line_in_file, " ");
		char temp_filename[MAX_FILENAME_LEN + 1];
		long int temp_filesize = 0;
		do
		{
			if (counter == 1)
			{
				strcpy(temp_username, part_of_line);
			}
			else if (counter == 2)
			{
				strcpy(temp_pwd, part_of_line);
			}
			else if (counter == 3)
			{
				char tmpStr[10];
				strcpy(tmpStr, part_of_line);
				num_of_files = atoi(tmpStr);
			}
			else
			{
				if (counter % 2 == 0)
				{
					strcpy(temp_filename, part_of_line);
					num_of_files++;
				}
				else
				{
					sscanf(part_of_line, "%ld", &temp_filesize);
					add_file((*user)->files, temp_filename, temp_filesize);
		
				}
			}
			part_of_line = strtok(NULL, " ");
			counter++;
		} while ((part_of_line != NULL));
		
		if (strcmp(temp_username, username) == 0 && strcmp(temp_pwd, pwd) == 0)
		{
			printf("Found -> username: %s, password: %s\n", temp_username, temp_pwd); /* DEBUG STATEMENT */ 
			strcpy((*user)->username, temp_username); 
			strcpy((*user)->pwd, temp_pwd);
			(*user)->line = line;
			(*user)->num_files = num_of_files;
			fclose(file);

			return 1;
		}
		else
		{
			printf("User not found\n");
			printf("Number of files: %d\n", num_of_files);
			(*user)->files = NULL; 
			(*user) = NULL;

			
		}
	}
	return 0;
}
/*******************************************************************************
 * Author: Gabriel Bogomolets
 * Since the head of linked list after creation is blank, this function will 
 * delete the invalid head of the linked list, and shift all the elements.
 * inputs:
 * - file_t *head: Pointer to the current first element of the list
 * outputs: none
*******************************************************************************/
file_t* removeHead(file_t* files)
{
	file_t *temp = files;
	file_t *holder;
	if (!(temp==NULL))
	{
		holder = temp->next;
		free(temp);
		files = holder;
	}
	return files;
}
/*******************************************************************************
 * Author: Oliver Windall Juhl
 * Basic helper function to print the elements of the linked list.
 * (DEBUGGING PURPOSES)
 * inputs:
 * - file_t *head: Pointer to the current first element of the list
 * outputs: none
*******************************************************************************/
void print_files(file_t* files)
{
  file_t *current = files;
  while (current != NULL)
  {
    printf("User has file %s with size %i\n", current->filename, current->size);
    current = current->next;
  }
}

/*******************************************************************************
 * Author: Oliver Windall Juhl / Gabriel Bogomolets
 * This function adds a file struct to the linked list of files. Currently, we
 * save only filename and size withing the elements of the linked list.
 * inputs:
 * - file_t *head: Pointer to the current first element of the list
 * - char filename[]: Name of the file to add
 * - int filesize: Size of the file to add
 * outputs:
 * - file_t: The new head of the linked list
*******************************************************************************/
void add_file(file_t *head, char filename[], int filesize)
{
  file_t *new_file = (file_t*)malloc(sizeof(file_t));
  strcpy(new_file->filename, filename);
  new_file->size = filesize;
  printf("test\n");
  new_file->next = NULL;
  if (head->next == NULL)
  {
	  printf("test\n");
	  head->next = new_file;
	  printf("test\n");
	  /* printf("Added at the beginning of linked list\n");   DEBUG STATEMENT */ 
  }
  else
  {
  	  file_t *current = head;
	  while (!(current->next == NULL))
	  {
	  	  current = current->next;
	  }
	  current->next = new_file;
	  /* printf("added Later\n");  DEBUG STATEMENT */ 
  }
  printf("Added file -> %s\n", filename); /* DEBUG STATEMENT */ 
}

/*******************************************************************************
 * Author: Matty B
 * This function checks whether the password is valid and returns a boolean flag
 * inputs:
 * - char password[]: A string containing the password
 * outputs:
 * - int valid: A boolean variable storing the validity of the password
*******************************************************************************/
int valid_password(char password[])
{
  int valid = 0;

  /* CHECKING THE SIZE OF PASSWORD */
  if ((strlen(password) < 6) || (strlen(password) > 16))
  {
    return valid;
  }
  /* LOOP THROUGH THE PASSWORD */
  int i;
  for (i = 0; i < strlen(password); i++)
  {

    /* CHECKING FOR ANY SPECIAL CHARACTERS */
    if (('a' <= password[i] && password[i] <= 'z') && ('A' <= password[i] && password[i] <= 'Z') && ('0' <= password[i] && password[i] <= '9'))
    {
      valid = 1;
      return valid;
    }
    else
    {
      return valid;
    }
  }
  return valid;
}

/*******************************************************************************
 * Author: Gabriel
 * This function prints the initial menu for the user
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_auth_menu(void)
{
  printf("Choose two options: \n");
  printf("Login - Press 1\n");
  printf("Register User - Press 2\n");
  printf("Exit Program - Press 3\n");
}

/*******************************************************************************
 * Author: Gabriel
 * This function handles the login authentication by obtaining all the login
 * information and running the appropiate tasks
 * inputs: none
 * outputs: none
*******************************************************************************/
void login(user_t** user)
{
  int valid = 0;
  char username[MAX_USERNAME_LEN + 1];
  char pwd[MAX_PWD_LEN + 1];

  printf("Enter login details or press B to go back\n");
  do
  {
    print_login();
    printf("Enter username: ");
    scanf("%s", username);
    if (strcmp(username, "b") == 0)
    {
      main();
    }
    printf("Enter password: ");
    scanf("%s", pwd);
    if (strcmp(pwd, "b") == 0)
    {
      main();
    }
    valid = find_user(username, pwd, user);
  } while (valid == 0);

  printf("User succesfully logged in!\n");
}

/*******************************************************************************
 * Author: Gabriel
 * This function prints the login user interface for the user
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_login(void)
{
  printf("Enter username and password followed by a space\n");
  printf("Or enter 'b' to go back\n");
}