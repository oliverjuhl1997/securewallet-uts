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
#define ENCRYPTION_KEY 0xFACA
#define ENCRYPTION_KEY_LEN 6

struct file
{
  char filename[MAX_FILENAME_LEN];
  int size;
  struct file *next;
};

typedef struct file file_t;

struct user
{
  char username[MAX_USERNAME_LEN + 1];
  char pwd[MAX_PWD_LEN + 1];
  int line;
  int num_files;
  file_t *files;
};

typedef struct user user_t;


int main(void);
/* Print related functions */
void print_auth_menu(void);
void print_login(void);
/* Authentication related functions */
int find_user(char username[], char pwd[], user_t** user);
int valid_password(char password[]);
void register_user(void);
file_t* removeHead(file_t* files);
void login(user_t** user);
void auth_choice(int choice, user_t** user); 
/* Encryption related functions */
void enter_file(user_t** usr);
void encrypt_file(char filename[], user_t** usr);
char xor_encryption(char pwd);
int calculcateSize(char filename[]);
/* Loading a user related functions*/
void add_file(file_t *head, char filename[], int file_size);
void print_files(file_t* user);
/* Options related functions */
void options_main(user_t** usr);
void print_options(void);
void auth_option_choice(int choice, user_t** user);