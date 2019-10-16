/*******************************************************************************
description: This is the header file for the program. What goes before the
main function.
 *******************************************************************************/

#include <stdio.h>  /* scanf,printf,getchar,fgets,fclose,fwrite,fread,fopen */
#include <string.h> /* strcpy,strcmp,strlen */
#include <stdlib.h> /* exit,malloc,free */

#define MAX_USERNAME_LEN 20
#define MAX_FILENAME_LEN 20
#define MAX_PWD_LEN 20
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
void saveUser(user_t** usr);
int valid_password(char password[]);
void register_user(void);
file_t* removeHead(file_t* files, int num);
void login(user_t** user);
void auth_choice(int choice, user_t** user); 
/* Encryption related functions */
void enter_file(user_t** usr);
void encrypt_file(char filename[], user_t** usr);
char xor_encryption(char pwd);
int calculcateSize(char filename[]);
/* Decryption related functions */
void decrypt_file(user_t** usr);
void decryption(char filename[], char newFile[], user_t** usr);
/* Loading a user related functions*/
void add_file(user_t** user, char filename[], int file_size);
void print_files(file_t* user);
/* Options related functions */
void options_main(user_t** usr);
void print_options(void);
void auth_option_choice(int choice, user_t** user);

file_t* createFile(char filename[], int filesize, file_t* next);
file_t* addHead(char filename[], int filesize, file_t* head);
file_t* addFile(char filename[], int filesize, file_t* head);
file_t* removeNode(file_t* head, int files, char filename[]);

int removeNewLine(int checkOnce);
int checkChar(char letter, char minLetter, char maxLetter);

/* Searching and sorting functions */
void dispFile_Menu(file_t* files);
void dispFile_Options(file_t* files);

void searchFiles(file_t* files);
void sorting_Options(file_t* files);

void sort_alph(file_t* files);
void sort_alph_rev(file_t* files);
void sort_size_asc(file_t* files);
void sort_size_desc(file_t* files);
void swap_files(file_t *ptr_a, file_t *ptr_b);
void swap(file_t *a, file_t *b);

void print_dispFile_options(void);
void print_sorting_options(void);

void print_result(file_t *current);