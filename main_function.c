/*******************************************************************************
 The main function of the program
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

int main(int argc, char *argv[])
{
	if (argv[1] != NULL && strcmp(argv[1], "-a") == 0)
	{
		printf("------ Authors ------ \n");
		printf("Gabriel Bogomolets\n");
		printf("Matt Gayoso\n");
		printf("Clark Kong\n");
		printf("Alistair Coomber\n");
		printf("Oliver Juhl\n");
		return 0;
	}
	else if (argv[1] != NULL && strcmp(argv[1], "-h") == 0)
	{
		printf("------ Help ------ \n");
		printf("This is Digital Secure Wallet.\n");
		printf("Store your file encrypted in your locally stored database, \n");
		printf("to ensure security on your filesystem.\n");
		printf("Simply make a new user and start encrypting your files!\n");
		return 0;
	}
	int choice;
	user_t *user;
	user = malloc(sizeof(user_t));
	user->files = NULL;
	while (strlen(user->username) == 0 || strlen(user->pwd) == 0)
	{
		printf(" -------- Welcome to Digital Secure Wallet! --------\n");
		print_auth_menu();
		scanf("%d", &choice);
		auth_choice(choice, &user);
	}
	/* User has logged in */
	printf("\n"
				 "------ Welcome %s! ------ \n",
				 user->username);
	printf("\n");
	options_main(&user);
	return 0;
}