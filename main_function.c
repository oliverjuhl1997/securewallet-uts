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
	user = NULL;
	printf("Initial value of name is %s \n", user->username);
	while(user == NULL)
	{
		print_auth_menu();
		scanf("%d", &choice);
		auth_choice(choice, &user);
		printf("Username in main is %s \n", user->username);
	}

	while (!(user == NULL))
	{
		printf("Options\n");
		break;
	}
	return 0;
}