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
/* Print related functions */
void print_auth_menu(void);
void print_login(void);
/* Authentication related functions */
int find_user(char username[], char pwd[]);
int valid_password(char password[]);
void register_user(void);
void login(void);
void auth_choice(int choice); /* Dont forget to add user_t *user */
/* Encryption related functions */
void simple_encrypt(char pwd[]);
void simple_decrypt(char pwd[]);
void xor_encryption(char pwd[]);