#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_files.h"

/* Include subroutines here boys */
/* Don't forget to update the header_files.h */

/*inputs: files LL, maybe number of files*/


/*	char newlinebuffer[4];
	char spacebuffer[4];
*/
	/*char option_cpy[100];*/
	/*int i;*/
/*	int errPrevent = 0;
*/	/*int invalid = -1;
    int flag = 0;*/
    /*int a;*/
	/*int flag = 0;*/
/*	int a = 1;
*/
void dispFile_Menu(file_t* files){
	char option[10];

	while(1 == 1){

		print_dispFile_options();

		scanf("%101s", option);

/*    	strcpy(option_cpy, option);

		for(i = 0; i < strlen(option_cpy); i++){
			if(option_cpy[i] == ' ')
				option_cpy[i] = 'e';
		}*/

/*		if (strlen(option_cpy) == 1){
			errPrevent++;
		}

		if(errPrevent == 1){
			continue;
		}*/

		/*printf("\noption_cpy is '%s'\n", option);*/

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
                sorting_Options(files);
                break;

            case 3:
                return;
                break;


                	/*printf("Invalid option\n");*/
		}


	}
}

		/*if(getchar() == '\n');*/
		/*a = */
		/*while(1 == 1){*/


/*			fgets(option, 101, stdin);
*/


			/*int len=strlen(option);
			printf("\nInvalid input, string length is %d", len);
			if(option[1] != '\n'){
	   		option[len-1]='\0';
	   		continue;
	   	    }*/

/*
    	if ((strlen(option) > 0) && (option[strlen (option) - 1] == '\n'))
        	option[strlen (option) - 1] = '\0';*/
		/*if (a != 1) {*/
/*            while ((flag = getchar()) != EOF && flag != '\n')
                continue;
            if (flag == EOF) {
                flag = invalid;
            }
            option = -1;*/
        /*}*/

        /*else if(strchr == )*/



/*		if(atoi(option_cpy) == 1){
			searchFiles(user, (*user)->files);
			print_files((*user)->files);
		}
		else if(atoi(option_cpy) == 2)
			sorting_Options(user);

		else if(atoi(option_cpy) == 3){

			return;
		}

		else if(atoi(option_cpy) < 1 || atoi(option_cpy) > 3){
			printf("\nInvalid input\n");
			continue;
		}*/





/*void searchFiles(user_t** user){
	printf("searching files\n");

}*/

void sorting_Options(file_t* files){
	char sortingOption[100];

	while(1 == 1){
		print_sorting_options();
		scanf("%101s", sortingOption);


		if(atoi(sortingOption) < 1 || atoi(sortingOption) > 5
        	|| strlen(sortingOption) > 1){
			printf("\nInvalid option\n\n");
			continue;
        }



		switch(atoi(sortingOption)){
            case 1:
                sort_alph(files);
                break;

            case 2:
                sort_alph_rev(files);
                break;

            case 3:
                sort_size_asc(files);
                break;

            case 4:
                sort_size_desc(files);
                break;

            case 5:
                return;
                break;
		}
	}
}

void sort_alph(file_t* files){
	printf("Working at start of sort alph\n");
	int filesFound = 0;
	file_t *current = files;
	/*int temp;*/
	while(current != NULL){
		printf("Working before if statement\n");
		if(strcmp(current->filename, current->next->filename) > 0 && current->next != NULL){
			printf("Working inside if statement before swapfiles\n");
			filesFound++;
			swap_files(current, current->next);

			/*temp = current->size;
			current->size = current->next->size;
			current->next->size = temp;*/
		}
		if(filesFound == 1)
			printf("\nName                        Size\n");
		print_result(current);
		current = current->next;
	}
}

void sort_alph_rev(file_t* files){

}

void sort_size_asc(file_t* files){

}

void sort_size_desc(file_t* files){

}

void swap_files(file_t *ptr_a, file_t *ptr_b){
	printf("Working at start of swap_files\n");
    file_t temp;
/*    *temp = *ptr_a*/



    strcpy(temp.filename, ptr_a->filename);
    strcpy(ptr_b->filename, ptr_a->filename);
   	strcpy(ptr_a->filename, temp.filename);
   	temp.size = ptr_a->size;
   	ptr_b->size = ptr_a->size;
   	ptr_a->size = temp.size;
   	printf("Working at end of swap_files\n");
/*    char *filename = (char*) malloc(sizeof(char) * MAX_FILENAME_LEN);
    strcpy(filename,ptr_a->filename);
    strcpy(ptr_a->filename,ptr_b->filename);
    strcpy(ptr_b->filename,filename);*/
    /*free(filename);*/
}

/* void print_files(file_t* files)
{
  file_t *current = files;
  while (current != NULL)
  {
    printf("User has file %s with size %i\n", current->filename, current->size);
    current = current->next;
  }
} */

void searchFiles(file_t* files){


	int filesFound = 0;
	file_t *current = files;
	char searchString[20];
	printf("Enter a file to search for or '*' to show all files\n");
	scanf("%s", searchString);

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

void print_result(file_t *current){
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


/*	else{
		while (current != NULL){
			if(strstr(current->filename, searchString) != NULL)
		}*/

	/*dispFile_Menu(user);*/


/*	file_t* new = (file_t*) malloc(sizeof(file_t));
	new->index = */