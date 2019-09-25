/*******************************************************************************
 The main function of the program

*******************************************************************************/
#include "headerFiles.h"
#include <stdio.h> 

int main(void) {
	int inp;

	print_auth_menu();
	while (!(inp == 1 || inp == 2)) {
		printf("Get input: \n");
		scanf("%d", &inp);
	}

	return 0;
}