#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"


/*******************************************************************************
 * Author: Oliver Windall Juhl
 * Basic helper function to print the elements of the linked list.
 * (DEBUGGING PURPOSES)
 * inputs:
 * - file_t *head: Pointer to the current first element of the list
 * outputs: none
*******************************************************************************/
void print_files(file_t *files)
{
	file_t *current = files;
	while (current != NULL)
	{
		printf("User has file %s with size %i\n", current->filename, current->size);
		current = current->next;
	}
}

/*******************************************************************************
 * Author: Gabriel
 * This function prints the initial menu for the user
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_auth_menu(void)
{
	printf("Select an option>\n");
	printf("-----------> (1) Login User\n");
	printf("-----------> (2) Register User\n");
	printf("-----------> (3) Quit Program\n");
}

/*******************************************************************************
 * Author: Gabriel
 * This function prints the login user interface for the user
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_login(void)
{
	printf("Enter username and password followed by a space\n");
	printf("Or enter 'b' to go back\n");
}

int checkChar(char letter, char minLetter, char maxLetter)
{
	if ((letter >= minLetter) && (letter <= maxLetter))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*******************************************************************************
 * Author: Gabriel
 * This function prints the options user interface for the user
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_options(void)
{
	printf("Select an Option!\n");
	printf(" --------> (1) Display Files\n");
	printf(" --------> (2) Encrypt File\n");
	printf(" --------> (3) Decrypt File\n");
	printf(" --------> (4) Logout\n");
}

void print_disp_file_options(void)
{
	printf("\n------ Display Files ------\n");
	printf("\nSelect an option\n");
	printf(" --------> (1) Search for file(s)\n");
	printf(" --------> (2) Sort files\n");
	printf(" --------> (3) Return to main menu\n");
}

void print_sorting_options(void)
{
	printf("Select a method for sorting or '5' to go back\n");
	printf(" --------> (1) Alphabetical order\n");
	printf(" --------> (2) Reverse alphabetical order\n");
	printf(" --------> (3) Increasing size\n");
	printf(" --------> (4) Decreasing size\n");
	printf(" --------> (5) Return to display files menu\n");

}