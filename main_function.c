/*******************************************************************************
 The main function of the program

*******************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "headerFiles.h"

int main(void) {
	int choice;
	user_t *user = NULL;

	while(user == NULL)
	{
		print_auth_menu();	
		scanf("%d", &choice);	
		auth_choice(choice);
	}

	while (!(user == NULL))
	{
		printf("Options\n");
	}
	return 0;
}