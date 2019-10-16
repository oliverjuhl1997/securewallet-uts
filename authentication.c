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
	int valid = 0;
	char username_buffer[200]; 
	char pwd_buffer[200]; 
    char string[200];
	char usernameString[200];
	int checkOnce = 1;

	while (valid == 0)
	{
		printf("Enter username>\n");
		checkOnce = removeNewLine(checkOnce);

		/* Gets the input using fgets and then checks if an empty
        line is entered */
        char *usr_pointer = username_buffer;
        fgets(username_buffer, 4096, stdin);
        if (sscanf(username_buffer, "%s", usernameString) == -1)
        {
            printf("Invalid empty line\n");
            continue;
        }
        /* Checks for spaces in the line */
        if ((usr_pointer = strpbrk(usr_pointer, " ")))
        {
            printf("No spaces allowed\n");
            continue;
        }
		/*Check length of string */
		if ((strlen(usernameString) >= 1) && (strlen(usernameString) <= MAX_USERNAME_LEN))
		{
			valid = 1;
		}
	}
	
	/* Reinitalize valid for checking password */
	valid = 0;
	while (valid == 0)
	{
		printf("Enter password>\n");
        /* Gets the input using fgets and then checks if an empty
        line is entered */
        char *pwd_pointer = pwd_buffer;
        fgets(pwd_buffer, 4096, stdin);
        if (sscanf(pwd_buffer, "%s", string) == -1)
        {
            printf("Invalid empty line\n");
            continue;
        }
        /* Checks for spaces in the line */
        if ((pwd_pointer = strpbrk(pwd_pointer, " ")))
        {
            printf("No spaces allowed\n");
            continue;
        }
		valid = valid_password(string);
	}
	FILE *file = NULL;

	file = fopen(DB_NAME, "a");
	if (file == NULL)
	{
		printf("Unable to open file at path: %s\n", DB_NAME);
	}
	if (calculcateSize(DB_NAME) == 0)
	{
		fprintf(file, "%s %s %i", usernameString, string, 0);
	}
	else
	{
		fprintf(file, "\n%s %s %i", usernameString, string, 0);
	}
	
	fclose(file);
	printf("Successfully registered user\n\n");
}

int removeNewLine(int checkOnce)
{
	char buffer[200]; 
    if (checkOnce == 1)
	{
		getchar();         
        buffer[strcspn(buffer, "\n")] = 0;
		checkOnce++;
	}
	return checkOnce;
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
	/* Create a pointer storing the file */
	FILE *file = NULL;
	file = fopen(DB_NAME, "r");
	/* Store the line of the file that the user is in */
	int line = 0;

	/* Check if file exists */
	if (file == NULL)
	{
		printf("Unable to open file at path: %s\n", DB_NAME);
		return 0;
	}
	/* Allocate Memory to user and files */
	char line_in_file[512];
	(*user) = malloc(sizeof(user_t));
	(*user)->files = malloc(sizeof(file_t));

	/* Loop through each line in the database */
	while (fgets(line_in_file, 512, file))
	{	
		/* Create temporary linked list */
		file_t* head = NULL;
		/* Temporary username, password and number of files in each line */
		char temp_username[MAX_USERNAME_LEN + 1];
		char temp_pwd[MAX_PWD_LEN + 1];
		int num_of_files = 0;
		/* Counter is used to check the content of text file */
		int counter = 1;
		int first_file = 0;
		/* Stores each section of the line */
		char *part_of_line = strtok(line_in_file, " ");
		/* Temporary filename and filesize */
		char temp_filename[MAX_FILENAME_LEN + 1];
		long int temp_filesize = 0;

		line++;
		do
		{
			/* Get the username part of line */
			if (counter == 1)
			{
				strcpy(temp_username, part_of_line);
			}
			/* Get the password part of the line */
			else if (counter == 2)
			{
				strcpy(temp_pwd, part_of_line);
			}
			/* Get the number of files and convert to int */
			else if (counter == 3)
			{
				char tmpStr[10];
				strcpy(tmpStr, part_of_line);
				num_of_files = atoi(tmpStr);
			}
			/* Now looping through each file */
			else
			{
				/* Check that files exist */
				if (num_of_files > 0)
				{
					/* Get the filename */
					if (counter % 2 == 0)
					{
						strcpy(temp_filename, part_of_line);
					}
					else
					{
						first_file++;
						sscanf(part_of_line, "%ld", &temp_filesize);

						/* If first file in line, set it as the head of the linked list */
						if (first_file == 1)
						{
							head = addHead(temp_filename, temp_filesize, head);
						}
						/* Append everyother file to the linked list */
						else
						{
							head = addFile(temp_filename, temp_filesize, head);
						}
					}
				}
			}
			part_of_line = strtok(NULL, " ");
			counter++;
		} while ((part_of_line != NULL));
		
		/* Check that the inputed username and password is equal to the details in the line */
		if (strcmp(temp_username, username) == 0 && strcmp(temp_pwd, pwd) == 0)
		{
			printf("Found -> username: %s, password: %s and number of files is %d\n", temp_username, temp_pwd, num_of_files); /* DEBUG STATEMENT */ 
			/* Copy the username and pwd to the user structure */
			strcpy((*user)->username, temp_username); 
			strcpy((*user)->pwd, temp_pwd);
			/* Copy line number and number of files to user structure */
			(*user)->line = line;
			(*user)->num_files = num_of_files;
			/* Set the head of the user's file linked list to the temporary created earlier */
			(*user)->files = head;
			fclose(file);

			return 1;
		}
		else
		{
			/* Reset temporary linked list before checking a new line */
			head = NULL;
			num_of_files = 0;
			printf("User not found\n");
			
		}
	}
	return 0;
}

file_t* createFile(char filename[], int filesize, file_t* next)
{
	/* Allocate memory for new file */
    file_t* new_file = (file_t*)malloc(sizeof(file_t));

	/* Error checking */
    if(new_file == NULL)
    {
        printf("Error creating a new file.\n");
		return NULL;
    }
	
	/* Add the file information to the newly created structure */
	strcpy(new_file->filename, filename);
	new_file->size = filesize;

	/* Linked the file and the linked list */
    new_file->next = next;
 
    return new_file;
}

file_t* addHead(char filename[], int filesize, file_t* head)
{
	/* Create the head struct and set the address of the head to the new file */
    file_t* new_file = createFile(filename, filesize, head);
    head = new_file;

    return head;
}
file_t* addFile(char filename[], int filesize, file_t* head)
{
	/* Check if the head is NULL*/
    if(head == NULL)
        return NULL;

	/* Iterate to the last file */
    file_t* current = head;
    while(current->next != NULL)
        current = current->next;
 
    /* Create a new file and append the end of the linked list to the new file */
    file_t* new_file =  createFile(filename, filesize, NULL);
    current->next = new_file;
 
    return head;
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

void add_file(user_t** user, char filename[], int filesize)
{
  file_t *new_file = (file_t*)malloc(sizeof(file_t));
 /* (*user)->files = malloc(sizeof(file_t)); */
  strcpy(new_file->filename, filename);
  new_file->size = filesize;
  new_file->next = NULL;

  if ((*user)->files->next == NULL)
  {
	  (*user)->files->next = new_file;
	  /* printf("Added at the beginning of linked list\n");   DEBUG STATEMENT */ 
  }
  else
  {
  	  file_t *current = (*user)->files;

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
  if ((strlen(password) <= 6) || (strlen(password) >= 20))
  {
	printf("Password must be between 6 and 20 characters long\n");
    return valid;
  }
  /* LOOP THROUGH THE PASSWORD */
  int i;
  int lower_case_count = 0;
  int upper_case_count = 0;
  int number_count = 0;
  for (i = 0; i < strlen(password); i++)
  {

    /* CHECKING FOR ANY SPECIAL CHARACTERS */
    if (checkChar(password[i], 'a', 'z'))
    {
	  lower_case_count++;
    }
    else if (checkChar(password[i], 'A', 'Z'))
    {
	  upper_case_count++;
    }
	else if (checkChar(password[i], '0', '9'))
	{
		number_count++;
	}
	else
	{
		printf("Invalid character\n");
		return valid;
	}
  }
  if ((lower_case_count >= 1) && (upper_case_count >= 1) && (number_count >= 1))
  {
		valid = 1;
		return valid;
  }
  else
  {
	printf("Password MUST contain at least an uppercase, lowercase and an integer\n");
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
  printf("Select an option>\n");
  printf("-----------> (1) Login User\n");
  printf("-----------> (2) Register User\n");
  printf("-----------> (3) Quit Program\n");
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

int checkChar(char letter, char minLetter, char maxLetter)
{
    if ((letter >= minLetter) && (letter <= maxLetter))
    {
        return 1;
    }
    else 
    {
        return 0;
    }

}