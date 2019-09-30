/*******************************************************************************

description: This is the header file for the program. What goes before the 
main function. 


 *******************************************************************************/

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

int main(void);
void print_auth_menu(void);
int valid_password(char password[]);
int find_user(char username[], char pwd[]);
void auth_choice(int choice); /* Dont forget to add user_t *user */
void register_user(void);
void login(void);
void print_login(void);