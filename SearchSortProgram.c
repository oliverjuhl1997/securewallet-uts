/***************************************************************************	
    *An example files array is initialised in the main and its size is taken
    *Menus print an error and loop for most invalid inputs (non-integer)

    Still to change: *Line 109; previous part of program should be called
                      instead of exiting the whole program.
                     *Possibly the format of displayed files

    Bugs: 2 error messages printed if a decimal number is entered
****************************************************************************/

#include <stdio.h> /* getchar, printf, scanf, */
#include <stdlib.h> /* None */
#include <string.h> /* strcmp, strstr,  */
#include "header_files.h"


void searchSort(file_t userFiles[], int numFiles);

void sortingMethod(file_t userFiles[], int numFiles);


void searchFiles(file_t userFiles[], int numFiles);

void printFiles(const file_t userFiles[], int numFiles, int i, int filesFound);

void swap(file_t *ptr_a, file_t *ptr_b);

void sortSize_asc(file_t userFiles[], int numFiles);
void sortSize_desc(file_t userFiles[], int numFiles);

void sortName_asc(file_t userFiles[], int numFiles);
void sortName_desc(file_t userFiles[], int numFiles);


int main(void){

	int a;

	file_t userFiles[] = {{"file1", 23}, 	  {"file2", 86}, 
                          {"document4", 54},  {"document3", 92}, 
                          {"emailpwd", 14}, {"workpwd", 18}};    

    int numFiles = sizeof(userFiles) / sizeof(userFiles[0]);


    a = sizeof(numFiles); /* IGNORE */

    printf("%d (ignore)\n", a); /* IGNORE */

    searchSort(userFiles, numFiles);

	return 0;
}

/*******************************************************************************
 * Author: Alistair
 * This function takes the users choice to search or sort the files.
 * inputs: userFiles array and the number of files.
 * outputs: Return 0 to return to main menu 
*******************************************************************************/
void searchSort(file_t userFiles[], int numFiles){

    int invalid = -1;
    int searchSortOpt;
    int flag = 0;

    while(flag != 1){
        printf("\n1. Search for a file\n");
        printf("2. Sort files\n");
        printf("3. Return to previous menu\n");
        printf("Enter choice (number from 1-3):\n");

        if (scanf("%d", &searchSortOpt) != 1) {
            while ((flag = getchar()) != EOF && flag != '\n')
                continue;
            if (flag == EOF) {
                flag = invalid;
            }
            searchSortOpt = -1;
        }

        switch(searchSortOpt){
            case 1:
                searchFiles(userFiles, numFiles);
                break;

            case 2:
                sortingMethod(userFiles, numFiles);
               break;

            case 3:
                exit(0); /* This will need to call upper level of program  */
                break;
               
            default:
                flag = invalid;
                printf("Invalid option!\n");
        
        }
    }
}

void sortingMethod(file_t userFiles[], int numFiles){
    
    int invalid = - 1;
    int valid = 1 ;
    int methodChoice;
    int flag = 0;

    while(flag != 1){
        printf("\nFiles may be sorted by the following methods:\n");
        printf("1. Alphabetically\n");
        printf("2. Backwards alphabetically\n");
        printf("3. Ascending by file size\n");
        printf("4. Descending by file size\n");
        printf("Enter sorting choice (number between 1-4) ");
        printf("or press '5' to go back:\n");
    
        if (scanf("%d", &methodChoice) != 1){
            while ((flag = getchar()) != EOF && flag != '\n')
                continue;
            if (flag == EOF) {
                flag = invalid;
        }
        methodChoice = -1;
        }

        switch(methodChoice){
            case 1:
                sortName_asc(userFiles, numFiles);
                break;
    
            case 2:
                sortName_desc(userFiles, numFiles);
                break;
    
            case 3:
                sortSize_asc(userFiles, numFiles);
                break;
    
            case 4:
                sortSize_desc(userFiles, numFiles);
                break;

            case 5:
                searchSort(userFiles, numFiles);
                flag = valid;
                break;
    
            default:
                printf("Invalid option!\n");
        }
    }    
}

/*******************************************************************************
 * Author: Alistair
 * This function searches for files with a matching search string.
 * inputs: userFiles array and the number of files.
 * outputs: None 
*******************************************************************************/
void searchFiles(file_t userFiles[], int numFiles){

    char searchString[MAX_FILENAME_LEN];
    int filesFound = 0;
    int i;

    printf("Enter a filename or enter * to show all files:\n");
    scanf("%s", searchString);

    for (i = 0; i < numFiles; i++){

        if ((!strcmp(searchString, "*")) 
            || strstr(userFiles[i].filename, searchString) != NULL){

            
            filesFound++;
            printFiles(userFiles, numFiles, i, filesFound);

        }
    }
    if (filesFound <= 0){
    printf("No files found\n");
    }
    searchSort(userFiles, numFiles);
}


/*******************************************************************************
 * Author: Alistair
 * This function prints the files and consistent spacing while inside a for loop.
 * inputs: * userFiles array and the number of files.
           * filesFound, if at least one file is found, the "Name - Size" title
             prints one time only, requires filesFound to be incrementing in the
             external for loop
           * i, element position of userFiles array 
 * outputs: None 
*******************************************************************************/
void printFiles(const file_t userFiles[], int numFiles, int i, int filesFound){

    int filenameLen;
    int j;
    
    if (filesFound == 1){
        printf("\nName                          Size\n");
    }

    printf("%s.txt ", userFiles[i].filename);

    filenameLen = strlen(userFiles[i].filename);

    for (j = 0; j < MAX_FILENAME_LEN - filenameLen + 4; j++){
    	printf(".");
    }

    printf(" %d B\n", userFiles[i].size);
}

/*******************************************************************************
 * Author: Alistair
 * This function swaps two file_t type pointers. Whatever data is in the address
   of one will change to the address of the other.
 * inputs: * Two file_t type pointers 
 * outputs: None 
*******************************************************************************/
void swap(file_t *ptr_a, file_t *ptr_b){ 

    file_t temp = *ptr_a; 
    *ptr_a = *ptr_b; 
    *ptr_b = temp;
} 

/*******************************************************************************
 * Author: Alistair
 * This function sorts files ascending by size.
 * inputs: userFiles array and the number of files. 
 * outputs: None 
*******************************************************************************/
void sortSize_asc(file_t userFiles[], int numFiles){

   int i, j;
   int filesFound = 0;
   for (i = 0; i < numFiles-1; i++){       
  
        for (j = 0; j < numFiles-i-1; j++){
            if (userFiles[j].size > userFiles[j+1].size){
                swap(&userFiles[j], &userFiles[j+1]);              
            }
        }    
    }
    printf("\nSorting by increasing size\n");
    for (i = 0; i < numFiles; i++){
        filesFound++;
        printFiles(userFiles, numFiles, i, filesFound);
    }
    sortingMethod(userFiles, numFiles);
}

/*******************************************************************************
 * Author: Alistair
 * This function sorts files descending by size.
 * inputs: userFiles array and the number of files. 
 * outputs: None 
*******************************************************************************/
void sortSize_desc(file_t userFiles[], int numFiles){

    int i, j;
    int filesFound = 0;
    for (i = 0; i < numFiles-1; i++){       
        for (j = 0; j < numFiles-i-1; j++){
            if (userFiles[j].size < userFiles[j+1].size){
                swap(&userFiles[j], &userFiles[j+1]);
            }
        }
    }
    for (i = 0; i < numFiles; i++){
        filesFound++;
    printFiles(userFiles, numFiles, i, filesFound);
    }
    sortingMethod(userFiles, numFiles);
}

/*******************************************************************************
 * Author: Alistair
 * This function sorts files in alphabetical order.
 * inputs: userFiles array and the number of files. 
 * outputs: None 
*******************************************************************************/
void sortName_asc(file_t userFiles[], int numFiles){
    
    int i, j;
    int filesFound = 0;

    for (i = 0; i < numFiles; i++){       
        for (j = 0; j < numFiles-i-1; j++){
            if (strcmp(userFiles[j].filename, userFiles[j+1].filename) > 0){
                swap(&userFiles[j], &userFiles[j+1]);
            }
        }
    }

    for (i = 0; i < numFiles; i++){
        filesFound++;
        printFiles(userFiles, numFiles, i, filesFound);  
    }

    sortingMethod(userFiles, numFiles);
}


/*******************************************************************************
 * Author: Alistair
 * This function sorts files in backwards alphabetical order.
 * inputs: userFiles array and the number of files. 
 * outputs: None 
*******************************************************************************/
void sortName_desc(file_t userFiles[], int numFiles){
    
    int i, j;
    int filesFound = 0;

    for (i = 0; i < numFiles; i++){       
        for (j = 0; j < numFiles-i-1; j++){
            if (strcmp(userFiles[j].filename, userFiles[j+1].filename) < 0){
                swap(&userFiles[j], &userFiles[j+1]);
            }
        }
    }

    for (i = 0; i < numFiles; i++){
        filesFound++;
        printFiles(userFiles, numFiles, i, filesFound);  
    }
    sortingMethod(userFiles, numFiles);
}
