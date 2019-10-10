/*******************************************************************************
 The main function of the program

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

int main(void) {
	int choice;
	user_t* user;
	user = malloc(sizeof(user_t));

	while(strlen(user->username) == 0 || strlen(user->pwd) == 0)
	{
		print_auth_menu();
		scanf("%d", &choice);
		auth_choice(choice, &user);
		printf("Head of file is -> %s \n", user->files->filename);
		print_files(user->files);
	}

	while (!(user == NULL))
	{
		printf("Options\n");
		break;
	}
	return 0;
}