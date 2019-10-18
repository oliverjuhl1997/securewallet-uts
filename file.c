#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

/*******************************************************************************
 * Author: Gabriel Bogomolets
 * This function allows the user to enter the name of a textfile they wish to
 * encrypt and call functions to encrypt it.
 * inputs:
 * - user_t** user: a double pointer containing the address of the user passed
 *					down from the main function
 * outputs: none
*******************************************************************************/
void enter_file(user_t **usr)
{
	int counter = 0;
	char filename_temp[MAX_FILENAME_LEN];
	printf("Enter the name of the file you wish to encrypt>\n");
	scanf("%s", filename_temp);
	encrypt_file(filename_temp, usr);
	counter++;
	return;
}

file_t *create_file(char filename[], int filesize, file_t *next)
{
	/* Allocate memory for new file */
	file_t *new_file = (file_t *)malloc(sizeof(file_t));

	/* Error checking */
	if (new_file == NULL)
	{
		printf("Error creating a new file.\n");
		return NULL;
	}

	/* Add the file information to the newly created structure */
	strcpy(new_file->filename, filename);
	new_file->size = filesize;

	/* Linked the file and the linked list */
	new_file->next = next;

	return new_file;
}

file_t *add_head(char filename[], int filesize, file_t *head)
{
	/* Create the head struct and set the address of the head to the new file */
	file_t *new_file = createFile(filename, filesize, head);
	head = new_file;

#ifdef DEBUG
	printf("DEBUG --- Added new file to empty list of files with name %s\n", filename);
#endif

	return head;
}

/*******************************************************************************
 * Author: Oliver Windall Juhl / Gabriel Bogomolets
 * This function adds a file struct to the linked list of files. Currently, we
 * save only filename and size withing the elements of the linked list.
 * inputs:
 * - file_t *head: Pointer to the current first element of the list
 * - char filename[]: Name of the file to add
 * - int filesize: Size of the file to add
 * outputs:
 * - file_t: The new head of the linked list
*******************************************************************************/
file_t *add_file(char filename[], int filesize, file_t *head)
{
	/* Check if the head is NULL*/
	if (head == NULL)
		return NULL;

	/* Iterate to the last file */
	file_t *current = head;
	while (current->next != NULL)
		current = current->next;

	/* Create a new file and append the end of the linked list to the new file */
	file_t *new_file = createFile(filename, filesize, NULL);
	current->next = new_file;

#ifdef DEBUG
	printf("DEBUG --- Added new file to list of files with name %s\n", filename);
#endif

	return head;
}