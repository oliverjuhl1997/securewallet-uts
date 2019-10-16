/*******************************************************************************
 The main function of the program
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

int main(void)
{
	int choice;
	user_t* user;
	user = malloc(sizeof(user_t));
	user->files = NULL;
	while(strlen(user->username) == 0 || strlen(user->pwd) == 0)
	{
		printf(" -------- Welcome to Digital Secure Wallet! --------\n");
		print_auth_menu();
		scanf("%d", &choice);
		auth_choice(choice, &user);
	}
	/* User has logged in */
	printf("\n"
			"------ Welcome %s! ------ \n", user->username);
	printf("\n");	
	options_main(&user);
	
	return 0;
}