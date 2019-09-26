/*****************************************************************************
Main and print statements to be removed




*/


#include <stdio.h>
#include <stdlib.h>

/*#define MAX_USERNAME_LEN 16
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
};*/

int auth_choice(int choice);
int getLogin(void);
void register_user(void);

/*******************************************************************************
 * This function uses a switch statement as a response to user input.
 * Two choices: 1 -> register, 2 -> login
 * inputs:
 * - int choice: The number used in the switch statement
 * outputs: none
 * - int user_id: an integer value containing the user_id (index) of the user
 * struct that has logged in.  User can either register or login - Allistair
*******************************************************************************/

int main (void){

	int choice;
	int flag;

	while(flag <= 1 || flag >= 2){
		printf("Enter 1 to login or 2 to register:\n");
		scanf("%d", &choice);


		flag = auth_choice(choice);
	}

	return 0;
}

int auth_choice(int choice) {

	switch(choice){
		case 1:
		getLogin();
		break;
		
		case 2:
		register_user();

		default:
		exit(0);
	}

	if(choice >= 1 && choice <= 2){
		
		return choice;
	}

	else{
		printf("Invalid input\n");
		return 0;
	}

} 

int getLogin(void){
	printf("getlogin starts\n");

	return 0;
}

void register_user(void){
	printf("register user starts\n");
}