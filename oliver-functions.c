/*******************************************************************************
 * This function adds the registered user information into a new structure 
 * of type user by firstly dynamically allocating memory and then storing the 
 * users information
 * inputs: 
 * - user_t *user: a pointer variable for the userId
 * - char username[]: a string containing the username for the user
 * - char password[]: a string containing the password for the user
*******************************************************************************/
user_t *create_user(user_t *userId, char username[], char password[]); /* Oliver */


/*******************************************************************************
 * This function writes the current user created to a database textfile (or binary)
 * file.
 * inputs:
 * - user_t *user: a variable pointing to the memory address of the user structure
 * outputs: none 
*******************************************************************************/
void save_users(user_t *user); /* Oliver */

/*******************************************************************************
 * This function loads the user details from an external text file database and 
 * saves them into an array of user structures
 * inputs:
 * - user_t *users[]: variable pointing to the address of list of users 
 * outputs: none
*******************************************************************************/
void loadUsers(user_t *users[]); /* Oliver */

/*******************************************************************************
 * This function handles all the tasks with registering the user. The function
 * will prompt the user for the information and register the user. 
 * We wil store: email, username, password, date created (ADD TO THIS)
 * inputs: none
 * outputs: none
*******************************************************************************/
void register_user(void); /* Oliver */