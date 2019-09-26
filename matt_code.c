#include <stdio.H>
#include <stdlib.h>

define SIZE 6;

int valpass(char password[])
{
    int i;
    
    for (i = 0; i < sizeof(password); i++)
    {
        if (isalnum(password[i])|| (ispunct(password[i])) ){
            return 0;
        } else
        {
            return 1;
        }
        
    
    }

    if (password > 6) && (password < 16)
    {
        
    }
    
}  