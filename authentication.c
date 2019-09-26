#include <stdio.h>  /* scanf,printf,getchar,fgets,fclose,fwrite,fread,fopen */
#include <string.h> /* strcpy,strcmp,strlen */
#include <stdlib.h> /* exit,malloc,free */

#define MAX_USERNAME_LEN 16
#define MAX_FILENAME_LEN 20
#define MAX_PWD_LEN 16
#define DB_NAME "database.txt"

struct file
{
  char filename[MAX_FILENAME_LEN];
  struct file *next;
};

typedef struct file file_t;

struct user
{
  char username[MAX_USERNAME_LEN + 1];
  char pwd[MAX_PWD_LEN + 1];
  file_t *files;
};

typedef struct user user_t;

void create_user();
void find_user();

int main(void)
{
  find_user();
  return 0;
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
void register_user()
{
  user_t user;
  file_t *head = NULL;

  scanf("%s %s", user.username, user.pwd);
  /* VALIDATE PASSWORD AND USERNAME*/
  user.files = head;

  FILE *file;
  file = fopen(DB_NAME, "a");
  if (file == NULL)
  {
    printf("Unable to open file at path: %s", DB_NAME);
  }
  fprintf(file, "%s %s", user.username, user.pwd);
  fclose(file);
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This function loads the user details from an external text file database and
 * saves them into an array of user structures
 * inputs: none
 * outputs: none
*******************************************************************************/
void find_user()
{
  FILE *file = NULL;
  file = fopen(DB_NAME, "r");
  if (file == NULL)
  {
    printf("Unable to open file at path: %s", DB_NAME);
    perror("Error");
    return;
  }

  char temp[512];
  char username[] = "oliverjuhl";
  char pwd[] = "pwd";

  while (fgets(temp, 512, file) != NULL)
  {
    char temp_username[MAX_USERNAME_LEN];
    char temp_pwd[MAX_USERNAME_LEN];
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
      char* user_info = details_ptr;
      printf("Found -> username: %s, password: %s", temp_username, temp_pwd);
      /* loads user */
    }
  }
  fclose(file);
}

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This adds a file to the current user
 * inputs: none
 * outputs: none
*******************************************************************************/
user_t load_user()

/*******************************************************************************
 * Author: Oliver Windall Juhl
 * This adds a file to the current user
 * inputs: none
 * outputs: none
*******************************************************************************/
void add_file()
{
}