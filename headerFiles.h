/*******************************************************************************

description: This is the header file for the program. What goes before the 
main function. 

 *******************************************************************************/
/*
#define MAX_USERNAME_LEN 16
#define MAX_FILENAME_LEN 20
#define MAX_FILES_LEN 5
#define MAX_PWD_LEN 16
#define DB_NAME "database.bin"

struct textFile {
	char filename[MAX_FILENAME_LEN];
};
typedef struct textFile file_t;

struct user {
	char username[MAX_USERNAME_LEN];
	char password[MAX_PWD_LEN];
	file_t *textFile[MAX_FILENAME_LEN]; 
	struct user *next;
};
typedef struct user user_t;
*/
void print_auth_menu(void);
/*
int auth_choice(int choice);
void register_user(void);
user_t *create_user(user_t *userId, char username[], char password[]);
int valid_password(char password[]);
void save_users(user_t *user);
int getLogin(void);
void printLoginUI(void);
void getLoginInfo(char *username[], char *pwd[]);
void loadUsers(user_t *users[]);
int validateLogin(user_t *users[]);
*/