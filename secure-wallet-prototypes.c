

/*
-----------------------------------------------------------
WORKING DRAFT FOR THE FUNCTIONS PROTOTYPES OF SECURE WALLET
-----------------------------------------------------------
*/

/* --------- Prototypes --------- */
/*******************************************************************************
 * This function prints the initial menu for the user and returns the authentication
 * Flag to the next menu
 * We support two options: register and login
 * inputs: none
 * outputs: 
 * - int user_id. Returns the user_id. user_id by default is set to -1 if 
 * if the password validation didn't work.
*******************************************************************************/
void print_auth_menu();

/*******************************************************************************
 * This function uses a switch statement as a response to user input.
 * Two choices: 1 -> register, 2 -> login
 * inputs:
 * - int choice: The number used in the switch statement
 * outputs: none
 * - int user_id: an integer value containing the user_id (index) of the user
 * struct that has logged in. 
*******************************************************************************/
int auth_choice(int choice); /* User can either register or login - Allistair*/

/*******************************************************************************
 * This function handles all the tasks with registering the user. The function
 * will prompt the user for the information and register the user. 
 * We wil store: email, username, password, date created (ADD TO THIS)
 * inputs: none
 * outputs: none
*******************************************************************************/
void register_user(void); /* Gabriel */

/*******************************************************************************
 * This function adds the registered user information into a new structure 
 * of type user by firstly dynamically allocating memory and then storing the 
 * users information
 * inputs: 
 * - user_t *user: a pointer variable for the userId
 * - char username[]: a string containing the username for the user
 * - char password[]: a string containing the password for the user
*******************************************************************************/
user_t *create_user(user_t *userId, char username[], char password[]); /* Gabriel */

/*******************************************************************************
 * This function checks the validity of a password.
 * We check the following:
 * 1. Greater than 6 and less than 16 characters
 * 2. No special characters (only integers and letters)
 * inputs:
 * - char password[]: The password we will check for validity
 * outputs:
 * - int: Returns 1 if password is valid else 0
*******************************************************************************/
int valid_password(char password[]); /* Checks password validity. Returns 1 if valid else 0 - MATT*/

/*******************************************************************************
 * This function writes the current user created to a database textfile (or binary)
 * file.
 * inputs:
 * - user_t *user: a variable pointing to the memory address of the user structure
 * outputs: none 
*******************************************************************************/
void save_users(user_t *user); /* Oliver */

/*******************************************************************************
 * This function signs a user in, it deals with all the login functionality.
 * inputs: none
 * outputs: 
 * - int user_id: returns the index of the structure that contains the user 
 * that just logged in. 
*******************************************************************************/
int getLogin(void);

/*******************************************************************************
 * This function prints the login user interface
 * inputs: none
 * outputs: none
*******************************************************************************/
void printLoginUI(void);

/*******************************************************************************
 * This function gets the username and password input from the user and stores
 * it in a pointer variable
 * inputs: 
 * - char *username[]: a variable pointing to the memory address of username
 * - char *pwd[]: a variable pointing to the memory address of pwd
 * outputs: none
*******************************************************************************/
void getLoginInfo(char *username[], char *pwd[]); /* MATT */

/*******************************************************************************
 * This function loads the user details from an external text file database and 
 * saves them into an array of user structures
 * inputs:
 * - user_t *users[]: variable pointing to the address of list of users 
 * outputs: none
*******************************************************************************/
void loadUsers(user_t *users[]); /* Oliver */

/*******************************************************************************
 * This function checks the inputted username and password against the ones stored
 * in the database file. Returning a boolean value if the match was successful
 * inputs: 
 * - user_t *users[]: variable pointing to an array of structures
 * outputs:
 * int flag: a flag boolean variable
*******************************************************************************/
int validateLogin(user_t *users[]); /* Gabriel */

/*******************************************************************************
 * This function signs a user out.
 * inputs: none
 * outputs: none
*******************************************************************************/
void logout(void);

/*******************************************************************************
 * This function prints the options menu to the user.
 * We generally support three areas:
 * - adding a file
 * - deleting a file
 * - displaying files
 * inputs: none
 * outputs: none
*******************************************************************************/
void print_options();

/*******************************************************************************
 * This function uses a switch statement as a response to user input.
 *  ------- CHOICES TO BE ANNOUNCED! -------
 * inputs:
 * - int choice: The number used in the switch statement
 * outputs: none
*******************************************************************************/
void options_choice(int choice);

/*******************************************************************************
 * This function adds a file connected to the current user.
 * inputs: none
 * outputs: none
*******************************************************************************/
void add_file();

/*******************************************************************************
 * This function will delete a file connected to the current user.
 * We will ensure connectivity to the user.
 * inputs: none
 * outputs: none
*******************************************************************************/
void delete_file();

/*******************************************************************************
 * This function will encrypt a file, such that only the connected user are
 * able to open and display it.
 * Will be used when adding a new file.
 * inputs: none
 * outputs: none
*******************************************************************************/
void encrypt_file();

/*******************************************************************************
 * This function will decrypt a file.
 * We will use user email and password to ensure, that the file is connected
 * to the user, that wishes to open it.
 * inputs:
 * - char email[]: User email
 * - char password[]: User password
 * outputs: none
*******************************************************************************/
void decrypt_file(char email[], char password[]);

/*******************************************************************************
 * This function will display all files connected to the current user.
 * We will use the user email to find the relevant files.
 * inputs:
 * - char email[]: User email
 * outputs: none
*******************************************************************************/
void display_all_files(char email[]);

/*******************************************************************************
 * This function will display all files that starts with the search_string.
 * We will match the search_string with file names.
 * inputs:
 * - char search_string[]: The string will be matched with filenames
 * outputs: none
*******************************************************************************/
void search_files(char search_string[]); /* Alternative to diplaying all users */

/*******************************************************************************
 * This function will sort files.
 * We support alphabetically, date created (ADD TO THIS)
 * inputs: none
 * outputs: none
*******************************************************************************/
void sort_files(); /* Many sorting methods could be supported - alphabetically, date created etc. */
