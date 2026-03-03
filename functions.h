#include <stdio.h>
#include <string.h>

typedef char longString[71]; //for steps 70 characters
typedef char shortString[21]; //for items 20 characters

struct foodTag
{
    shortString name;
    float       quantity;
    shortString unit;
    float       calories;
};

struct ingredientTag
{
    shortString item;
    float       quantity;
    shortString unit;
};

struct recipeTag
{
    shortString          title;
    shortString          classification;
    int                  servings;
    struct ingredientTag ingredients[20];
    longString           steps[15];
};

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

    printf("Enter username: ");
    scanf(" %s", user);
    printf("Enter password: ");
    scanf(" %s", pass);

    if (strcmp(user, userKey)==0 && strcmp(pass, passKey)==0)
    {
        printf("USER VALIDATED // SUCCESSFUL ENTRY\n");
        // update mode access
    }
        
    else
    {
        printf("Invalid username or password\n");
        //displayMain ();
    }
}


void getString (shortString str)
{
    char ch;
    int i = 0;

    do
    {
        scanf(" %c", &ch);

        while (ch != '\n')
        {
            if (i < 20)   // prevent overflow
            {
                str[i] = ch;
                i++;
            }

            scanf("%c", &ch);
        }

        str[i] = '\0';

        if (i == 0)
            printf("String cannot be empty. Please try again: ");

        if (i > 20)
            printf("String too long. Please try again: ");

    } while (i == 0);
}

int checkFoodName (struct foodTag foods[], int foodCount, shortString name)
{
    for (int i = 0; i < foodCount; i++)
    {
        if (strcmp(foods[i].name, name) == 0)
            return i; // return index of existing food
    }
    return -1; // not found
}

void foodCalories (struct foodTag foods[], int *foodCount)
{
    int i = *foodCount; // get current count of food entries
    shortString temp; // temporary string for food name input and checking

    do {
        printf("\nEnter food name: ");
        getString(temp);

        if (checkFoodName(foods, *foodCount, temp) != -1)
            printf("Food already exists at index %d. Please enter a different name.\n", checkFoodName(foods, *foodCount, temp));
        else
            strcpy(foods[i].name, temp);
    } while (checkFoodName(foods, *foodCount, temp) != -1);
    
    printf("Enter quantity: ");
    scanf(" %f", &foods[i].quantity);
    printf("Enter unit: ");
    getString(foods[i].unit);
    printf("Enter calories: ");
    scanf(" %f", &foods[i].calories);
    (*foodCount)++; // increment food count for next entry
}

void viewFoodCalories (struct foodTag foods[], int foodCount)
{
    /*
    Display all food entries in a formatted list.
    */
}

void saveCalories (struct foodTag foods[], int foodCount)
{
    /*
    Save the food entries to a file for later retrieval.
    */
}