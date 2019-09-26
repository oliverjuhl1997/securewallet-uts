#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerFiles.h"

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
void auth_choice(int choice)
{
  switch(choice){
    case 1:
    login();

    break;
    
    case 2:
    register_user();
    break;

    case 3:
    exit(0);

    default:
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

 Issues: If registering multiple users, the subroutine overwrites the line 
 rather than adding the username and password to a new line
*******************************************************************************/
void register_user(void)
{
  user_t user;
  file_t *head = NULL;
  
  printf("Enter usename: ");
  scanf("%s", user.username);
  printf("Enter password: ");
  scanf("%s", user.pwd);

  printf("%s", user.pwd);

  /* VALIDATE PASSWORD AND USERNAME*/
  printf("%d\n", valid_password(user.pwd));


  user.files = head;

  FILE *file = NULL;
  file = fopen(DB_NAME, "w");
  if (file == NULL)
  {
    printf("Unable to open file at path: %s", DB_NAME);
  }
  
  fprintf(file, "%s %s", user.username, user.pwd); 
  fclose(file);

  printf("successfully registered user\n\n");
  
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function loads the user details from an external text file database and
 * saves them into an array of user structures
 * inputs: none
 * outputs: none
*******************************************************************************/
int find_user(char username[], char pwd[])
{
  int valid = 0;
  FILE *file = NULL;
  file = fopen(DB_NAME, "r");
  if (file == NULL)
  {
    printf("Unable to open file at path: %s", DB_NAME);
    return 0;
  }

  char temp[512];

  while (fgets(temp, 512, file) != NULL)
  {
    char temp_username[MAX_USERNAME_LEN + 1];
    char temp_pwd[MAX_PWD_LEN + 1];
    char *details_ptr = strtok(temp, " ");
    int counter = 0;
    do
    {
      printf("%s \n", details_ptr);
      if (counter == 0)
      {
        strcpy(temp_username, details_ptr);
      }
      if (counter == 1)
      {
        strcpy(temp_pwd, details_ptr);
      }
      details_ptr = strtok(NULL, " ");
      counter++;
    } while ((details_ptr != NULL) && counter < 2);

    if (strcmp(temp_username, username) == 0 && strcmp(temp_pwd, pwd) == 0)
    {
      /*
      char* user_info = details_ptr; */
      printf("Found -> username: %s, password: %s", temp_username, temp_pwd);
      printf("Loading user...\n");
      valid = 1;
      return valid;
    } 
    else
    {
      printf("User not found\n");
      return valid;
    }
  }
  fclose(file);
  return valid;
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
    if ((strlen(password) < 6) || (strlen(password) > 16)) {
      return valid;
    } 
    /* LOOP THROUGH THE PASSWORD */
  int i;
  for (i=0; i<strlen(password); i++) {

    /* CHECKING FOR ANY SPECIAL CHARACTERS */
      if(('a' <= password[i] && password[i] <= 'z') && ('A' <=  password[i] && password[i] <= 'Z') && ('0' <=  password[i] && password[i] <= '9'))
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
void login(void) 
{
  int valid = 0;
  char username[MAX_USERNAME_LEN + 1];
  char pwd[MAX_PWD_LEN + 1];

  printf("Enter login details! (or press 'b' to go back) \n");
  do {
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
    valid = find_user(username, pwd);
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

