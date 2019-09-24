/*******************************************************************************

description: This is the header file for the program. What goes before the 
main function. 


 *******************************************************************************/

#define MAX_USERNAME_LEN 16;
#define MAX_FILENAME_LEN 20;
#define MAX_FILES_LEN 5;
#define MAX_PWD_LEN 16;
#define DB_NAME "database.bin";

struct textFile {
	char filename[MAX_FILENAME_LEN];
};
typedef struct textFile file_t;

struct user {
	char username[MAX_USERNAME_LEN];
	char password[MAX_PWD_LEN];
	file_t *textFile[MAX_FILENAME_LEN]; 
}