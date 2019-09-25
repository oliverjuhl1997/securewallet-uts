#include "headerFiles.h"
#include <stdio.h>
/*******************************************************************************
 * This function prints the initial menu for the user and returns the authentication
 * Flag to the next menu
 * We support two options: register and login
 * inputs: none
 * outputs: 
 * - int user_id. Returns the user_id. user_id by default is set to -1 if 
 * if the password validation didn't work.
*******************************************************************************/
void print_auth_menu(void) {
	printf(" ------------ Digital Secure Wallet!------------ \n");
	printf("Choose two options: \n");
	printf("Login - Press 1\n");
	printf("Register User - Press 2\n");
}

/*******************************************************************************
 * This function signs a user in, it deals with all the login functionality.
 * inputs: none
 * outputs: 
 * - int user_id: returns the index of the structure that contains the user 
 * that just logged in. 
*******************************************************************************/
int getLogin(void){
	return;
}


/******************************************************************************
 * This function prints the login user interface
 * inputs: none
 * outputs: none
*******************************************************************************/
void printLoginUI(void) {
	return;
}
