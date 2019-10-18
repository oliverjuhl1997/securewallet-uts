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

/* Entry point */
int main(int argc, char *argv[]);
void normal_mode();

/* Print */
void print_login(void);
void print_auth_menu(void);
void print_options(void);
void print_files(file_t* user);
void print_file_options(void);
void print_sorting_options(void);
void print_result(file_t *current);

/* User */
int find_user(char username[], char pwd[], user_t** user);
void save_user(user_t** usr);
void register_user(void);
void login(user_t** user);

/* File */
file_t* remove_head(file_t* files, int num);
void enter_file(user_t** usr);
int calculcate_size(char filename[]);
file_t* create_file(char filename[], int filesize, file_t* next);
file_t* add_head(char filename[], int filesize, file_t* head);
file_t* add_file(char filename[], int filesize, file_t* head);
file_t* remove_node(file_t* head, int files, char filename[]);
void swap_files(file_t *ptr_a, file_t *ptr_b);
void swap(file_t *a, file_t *b);

/* Encryption / decryption */
char xor_encryption_char(char pwd);
void xor_encryption(char pwd[]);
void decryption(char filename[], char newFile[], user_t** usr);
void encrypt_file(char filename[], user_t** usr);
void decrypt_file(user_t** usr);

/* Options */
void options_main(user_t** usr);
void user_option_choice(int choice, user_t** user);
void user_choice(int choice, user_t **user);
void file_options(file_t* files);
void sorting_options(file_t* files);


/* Searching and sorting */
void file_menu(file_t* files);
void search_files(file_t* files);
void sort_alph(file_t* files);
void sort_alph_rev(file_t* files);
void sort_size_asc(file_t* files);
void sort_size_desc(file_t* files);

/* Util */
int remove_new_line(int checkOnce);
int check_char(char letter, char minLetter, char maxLetter);
int valid_password(char password[]);
