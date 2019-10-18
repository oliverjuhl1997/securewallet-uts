#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"


void dispFile_Menu(file_t* files){
	char option[10];

	while(1) {

		print_dispFile_options();
		scanf("%101s", option);
		
        if(atoi(option) < 1 || atoi(option) > 3
        	|| strlen(option) > 1){
			printf("\nInvalid option\n\n");
			continue;
        }

		switch(atoi(option)){
            case 1:
                searchFiles(files);
                break;
            case 2:
                return;
				break;
		}
	}
}



void print_dispFile_options(void)
{
	printf("\n------ Display Files ------\n");
	printf("\nSelect an option\n");
	printf(" --------> (1) Search for file(s)\n");
	printf(" --------> (2) Return to main menu\n");
}

void searchFiles(file_t* files)
{
	int filesFound = 0;
	file_t *current = files;
	char searchString[20];

	printf("Enter a file to search for or '*' to show all files\n");
	scanf("%s", searchString);

#ifdef DEBUG
	printf("DEBUG ----- Searching for file %s\n", searchString);
#endif

	/* Traverse each linked list node until the value of a node is NULL */
	while (current != NULL){
		
		/* '*' input prints all files.
		   Any other filename containing the search string
		   will be printed */
		if (strcmp(searchString, "*") == 0 ||
			(strstr(current->filename, searchString) != NULL)){
			
			/* Making the title print once only, number of spaces is 24 */
			filesFound++;
			if(filesFound == 1)
				printf("\nName                        Size\n");

			print_result(current);
	
		}
		
		current = current->next;
	}

	/* Message to user if no matching files are found */
	if(filesFound == 0){
		printf("\nNo matching files found\n\n");
		
	}

}

void print_result(file_t *current)
{
			int i;
			printf("%s ", current->filename);

			/* Formatting, printing no. of '.' chars required to have
			   consistent spacing between 'Name' and 'Size' columns for
			   different filename lengths. */
			int filename_len = strlen(current->filename);
			for(i = 0; i < (MAX_FILENAME_LEN - filename_len + 6); i++)
				printf(".");

			printf(" %d B\n", current->size);
			
}
