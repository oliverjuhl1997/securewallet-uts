#include <stdio.h>
#include <stdlib.h>

int valid_password(char *password){

    /* CHECKING THE SIZE OF PASSWORD */
    if (strlen(password) < 6) || (strlen(password) > 16){
    	printf("Invalid input\n");
    }
  
    /* CHECKING FOR ANY SPECIAL CHARACTERS */
   if(('a' <=  password && password <= 'z') || ('A' <=  password && password <= 'Z') || ('0' <=  password && password <= '9'))
   {
      printf("Password valid\n", password);
   }
   else
   {
   	  printf("Invalid input\n");
   }
   return 0;

}