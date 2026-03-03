#include <stdio.h>
#include <string.h>

typedef char longString[71]; //for steps 70 characters
typedef char shortString[21]; //for items 20 characters

void mainMenu ()
{
    printf("============================\n");
    printf("| %24s |\n", " ");
    printf("| %4s MAIN MENU %9s |\n", " ", " ");
    printf("| %4s [U] Update Menu %4s|\n", " ", " ");
    printf("| %4s [A] Access Menu %4s|\n", " ", " ");
    printf("| %4s [E] Exit Menu %6s|\n", " ", " ");
    printf("| %24s |\n", " ");
    printf("============================\n\n");
}

int getChoice ()
{
    /*
    Make a function that:
    - reads the user’s choice (ex: U/A/E)
    - rejects invalid input and asks again
    - returns a clean, single choice your main can use
    */

    return -1; //if invalid choice
}

void displayMain ()
{
    /*
    Make a function that:
    - displays main menu
    - gets the user choice
    - LOOPS if the user's choice is invalid
    */
}

void updateMode ()
{
    shortString user;
    shortString pass;
    shortString userKey = "admin";
    shortString passKey = "ad1234";

    printf("Enter username: \n");
    scanf(" %s", &user);
    printf("Enter password: \n");
    scanf(" %s", &pass);

    if (strcmp(user, userKey)==0)
    {
        printf("USER VALIDATED // SUCCESSFUL ENTRY");
        // update mode access
    }
        
    else
    {
        printf("Invalid username or password\n");
        //displayMain ();
    }
}

void accessMode ()
{

}
