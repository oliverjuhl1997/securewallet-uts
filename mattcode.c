#include <stdio.h>
#include <stdlib.h>

int valid_password(char password[]) {

	int valid = 0;

    /* CHECKING THE SIZE OF PASSWORD */
    if (strlen(password) < 6) || (strlen(password) > 16){
    	return valid;
    } 
    /* LOOP THROUGH THE PASSWORD */
	int i;
	for (i=0; i<strlen(password); i++) {

		/* CHECKING FOR ANY SPECIAL CHARACTERS */
   		if(('a' <= password[i] && password[i] <= 'z') && ('A' <=  password[i] && password[i] <= 'Z') && ('0' <=  password[i] && password[i] <= '9'))
   		{
   			valid = 1;
      		return valid;
   		}
   		else
   		{
   	  		return valid;	
   		}
   	}
}