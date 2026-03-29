#include <stdio.h>
#include <string.h>
#include <ctype.h>  
#include <stdlib.h>
#include <time.h>

#define MAX_RECIPES 50
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
    int                  ingredientCount;
    longString           steps[15];
    int                  stepCount;
};

void longDivider()
{
    printf("|==============================================================================|\n");
}

void longDivider2()
{
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
}

void returnToMain()
{
    printf("\n");
    longDivider2();
    printf("==                         RETURNING TO MAIN MENU...                          ==\n");
    longDivider2();
    printf("\n");
}

void returnToUpdate()
{
    printf("\n");
    longDivider2();
    printf("==                        RETURNING TO UPDATE MENU...                         ==\n");
    longDivider2();
    printf("\n");
}

void returnToAccess()
{
    printf("\n");
    longDivider2();
    printf("==                        RETURNING TO ACCESS MENU...                         ==\n");
    longDivider2();
    printf("\n");
}

/*
This function checks two strings without caring about uppercase/lowercase. 
It returns: -1 if a < b, 0 if a == b (ignore case), and 1 if a > b
    @param a - first string to compare
    @param b - second string to compare
*/
int caseInsensitiveCompare(const char a[], const char b[])
{
    int i = 0;
    int result = 0;
    int foundDiff = 0;
    int ca,cb;

    while (a[i] && b[i])
    {
        if (!foundDiff)
        {
            ca = tolower(a[i]);
            cb = tolower(b[i]);

            if (ca != cb)
            {
                if (ca < cb)
                    result = -1;
                else
                    result = 1;

                foundDiff = 1; 
            }
        }

        i++;
    }

    if (!foundDiff)
    {
        if (a[i] == '\0' && b[i] == '\0')
            result = 0;
        else if (a[i] == '\0')
            result = -1;
        else
            result = 1;
    }

    return result;
}

// early declarations for some functions to avoid implicit declaration warnings 
// since they are called before their definitions
int getChoiceUpdate (int nChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount, shortString passKey);
void listRecipe (struct recipeTag recipes[], int recipeCount);
int getChoiceAccess (int nChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount);

/*
This function gets a valid integer input from the user.
    @param nChoice - pointer to the integer where the input will be stored
    Pre-condition: the user must input an integer
*/
void getValidIntInput(int *nChoice)
{
    int valid = 0;
    shortString discard;

    do
    {
        printf("|%3s --> Option: ", " ");
        if (scanf(" %d", nChoice) == 1)
            valid = 1;
        else
        {
            printf("|>                         Invalid Option! Try again.                         <|\n");
            scanf(" %20s", discard); // removes bad input, prevents infinite loop when invalid
        }
    } while (!valid);
}

/*
This function gets a string input from the user and stores it in the provided array.
    @param str - pointer to the array where the input will be stored
    Pre-condition: the user must input a string of at most 20 characters (not counting the null terminator)
*/
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

void updateMenu ()
{
    longDivider();
    printf("| %76s |\n", " ");
    printf("| %31s UPDATE MENU %32s |\n", " ", " ");
    printf("| %2s [1] Add Food Calories %52s|\n", " ", " ");
    printf("| %2s [2] View Food Calories %51s|\n", " ", " ");
    printf("| %2s [3] Save Calories %56s|\n", " ", " ");
    printf("| %2s [4] Load Calories %56s|\n", " ", " ");
    printf("| %2s [5] Add Recipe %59s|\n", " ", " ");
    printf("| %2s [6] Modify Recipe %56s|\n", " ", " ");
    printf("| %2s [7] Delete Recipe %56s|\n", " ", " ");
    printf("| %2s [8] List Recipes %57s|\n", " ", " ");
    printf("| %2s [9] Scan Recipe %58s|\n", " ", " ");
    printf("| %2s [10] Search Recipe %55s|\n", " ", " ");
    printf("| %2s [11] Export Recipe %55s|\n", " ", " ");
    printf("| %2s [12] Import Recipe %55s|\n", " ", " ");
    printf("| %2s [13] Change Password %53s|\n", " ", " ");
    printf("| %2s [14] Exit Update Menu %52s|\n", " ", " ");
}

void accessMenu ()
{
    longDivider();
    printf("| %76s |\n", " ");
    printf("| %32s ACCESS MENU %31s |\n", " ", " ");
    printf("| %2s [1] Import Recipe %56s|\n", " ", " ");
    printf("| %2s [2] List Recipes %57s|\n", " ", " ");
    printf("| %2s [3] Scan Recipe %58s|\n", " ", " ");
    printf("| %2s [4] Search Recipe %56s|\n", " ", " ");
    printf("| %2s [5] Generate Shopping List %47s|\n", " ", " ");
    printf("| %2s [6] Scan Recipes by Ingredient %43s|\n", " ", " ");
    printf("| %2s [7] Recommend Menu %55s|\n", " ", " ");
    printf("| %2s [8] Exit Access Menu %53s|\n", " ", " ");
}

void changePassword (shortString passKey)
{
    shortString oldPass;
    shortString newPass;
    shortString confirmPass;

    printf("\n");
    longDivider();
    printf(">                             CHANGING PASSWORD...                             <\n");
    longDivider2();
    printf("--> Enter current password: ");
    scanf(" %s", oldPass);

    if (strcmp(oldPass, passKey) == 0)
    {
        printf("--> Enter new password: ");
        scanf(" %s", newPass);
        printf("--> Confirm new password: ");
        scanf(" %s", confirmPass);

        if (strcmp(newPass, confirmPass) == 0)
        {
            strcpy(passKey, newPass);
            printf(">                        Password changed successfully!                        <\n");
            longDivider();
            printf("\n");
        }
        else
        {
            printf(">                       Does not match. Please try again.                      <\n");
            longDivider();
            printf("\n");
        }
    }
    else
    {
        printf(">                 Incorrect current password. Please try again                 <\n");
        longDivider();
        printf("\n");
    }

}
/*
This function handles the update mode of the program. It first validates the user by asking for a username and password. 
If the credentials are correct, it displays the update menu and processes the user's choices.
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - pointer to the integer that keeps track of how many food entries are currently stored
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - pointer to the integer that keeps track of how many recipe entries are currently stored
    @param passKey - the current password for accessing update mode, used for validating user login
    Pre-condition: the user must input valid credentials to access the update menu, and must input valid options when navigating the menu
*/
int updateMode (struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount, shortString passKey)
{
    int res;
    int nChoice;
    shortString user;
    shortString pass;
    shortString userKey = "admin";

    printf("-->%1s Enter username: ", " ");
    scanf(" %s", user);
    printf("-->%1s Enter password: ", " ");
    scanf(" %s", pass);
    
    if (strcmp(user, userKey)==0 && strcmp(pass, passKey)==0)
    {
        printf(">                           USER VALIDATED / SUCCESS                           <\n");
        longDivider();
        printf("\n");

        do
        {
            updateMenu();
            printf("|%78s|\n", " ");
            getValidIntInput(&nChoice);
            printf("|%78s|\n", " ");
            longDivider();
            res = getChoiceUpdate(nChoice, foods, foodCount, recipes, recipeCount, passKey); 
        } while (res == -1); //ends loop if invalid input or input is exit update menu
    }
        
    else
    {
        printf(">                         INVALID USERNAME OR PASSWORD                         <\n");
        longDivider();
        printf("\n");
        res = -1;
    }
    
    return res;
}

int accessMode (struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount)
{
    int res;
    int nChoice;

    do
    {
        accessMenu();
        printf("|%78s|\n", " ");
        getValidIntInput(&nChoice);
        printf("|%78s|\n", " ");
        longDivider();
        res = getChoiceAccess(nChoice, foods, foodCount, recipes, recipeCount);
    }while( res == -1); //ends loop if invalid input or input is exit access menu

    return res;
}

void mainMenu ()
{
    longDivider();
    printf("| %76s |\n", " ");
    printf("| %33s MAIN MENU %32s |\n", " ", " ");
    printf("| %30s [U] Update Menu %30s|\n", " ", " ");
    printf("| %30s [A] Access Menu %30s|\n", " ", " ");
    printf("| %30s [E] Exit Menu %32s|\n", " ", " ");
    printf("| %76s |\n", " ");
    longDivider();
    printf("\n");
}

/*
This function checks if a food name already exists in the array.
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - the number of food entries currently stored
    @param name - the name of the food to check
    @return - the index of the existing food if found, otherwise -1
*/
int checkFoodName (struct foodTag foods[], int foodCount, shortString name)
{
    int res = -1;

    for (int i = 0; i < foodCount; i++)
    {
        if (caseInsensitiveCompare(foods[i].name, name) == 0)
            res = i; // return index of existing food
    }
    return res; // not found
}

/*
This function checks if a recipe title already exists in the array.
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - the number of recipe entries currently stored
    @param title - the title of the recipe to check
    @return - the index of the existing recipe if found, otherwise -1
*/
int checkRecipeTitle (struct recipeTag recipes[], int recipeCount, shortString title)
{
    int res = -1;

    for (int i = 0; i < recipeCount; i++)
    {
        if (caseInsensitiveCompare(recipes[i].title, title) == 0)
            res = i; // return index of existing recipe
    }
    return res; // not found
}

/*
This function processes the user's choice in the main menu and directs them to the appropriate mode.
    @param cChoice - the character input representing the user's choice in the main menu
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - pointer to the integer that keeps track of how many food entries are currently stored
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - pointer to the integer that keeps track of how many recipe entries are currently stored
    @param passKey - the current password for accessing update mode, used for validating user login when they choose to enter update mode
*/
int getChoice (char cChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount, shortString passKey) 
{
    int res=1;
    
    switch(cChoice)
	{
		case 'U':
		case 'u':
            res = updateMode(foods, foodCount, recipes, recipeCount, passKey);
            if(res==0)
            {
                printf("\n");
                longDivider2();
                printf("|>                           Exiting Update Menu...                           <|\n");
                longDivider2();
                printf("\n");
                res=-1;
            }
			break;
		case 'A':
		case 'a':
			res = accessMode(foods, foodCount, recipes, recipeCount);
            if(res==0)
            {
                printf("\n");
                longDivider2();
                printf("|>                           Exiting Access Menu...                           <|\n");
                longDivider2();
                printf("\n");
                res=-1;
            }
			break;
		case 'E':
		case 'e':
            printf("\n");
            longDivider2();
            printf("|>                         Exiting Machine Project...                         <|\n");
            printf("|>       -----       Made By: Shenelle Nono and Marco Yatco       -----       <|\n");
            longDivider2();
            printf("\n");
			res=0;
			break;
		
		default: 
		{
			printf("\n");
            longDivider2();
            printf("|>                         Invalid Option! Try again.                         <|\n");
            longDivider2();
            printf("\n");
			res=-1;
		}
	}
	
	return res;
}

/*
This function displays the main menu and processes the user's choices until they choose to exit.
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - pointer to the integer that keeps track of how many food entries are currently stored
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - pointer to the integer that keeps track of how many recipe entries are currently stored
    @param passKey - the current password for accessing update mode, used for validating user login when they choose to enter update mode
*/
void displayMain (struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount, shortString passKey)
{
    char cChoice;
    shortString modeInput; //para mag invalid if more than 2 characs
    int res;
    do
	{
		mainMenu();
        longDivider2();
		printf("-->%1s Enter Mode: ", "");
        scanf(" %20s", modeInput);
        if (strlen(modeInput) == 1)
            cChoice = modeInput[0];
        else
            cChoice = '\0';
        longDivider2();
		
        res = getChoice(cChoice, foods, foodCount, recipes, recipeCount, passKey);
		
	}while(res==-1); //ends loop if invalid input or input is exit
	
}

/*
This function allows the user to add a new food calorie entry.
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - pointer to the integer that keeps track of how many food entries are currently stored, used to determine where to add the new entry and to increment after adding
    Pre-condition: the user must input a unique food name that does not already exist in the array, 
    and must input valid values for quantity and calories (quantity > 0, calories >= 0)
*/
void addFoodCalories (struct foodTag foods[], int *foodCount)
{
    int i = *foodCount; // get current count of food entries
    shortString temp; // temporary string for food name input and checking
    int scanResult;

    printf("\n");
    longDivider2();
    printf(">                           ADDING FOOD CALORIES...                            <\n");
    longDivider2();

    do {
        printf("--> Enter food name: ");
        getString(temp);

        if (checkFoodName(foods, *foodCount, temp) != -1)
            {
                printf("!                         Food exists // View Number %d                        !\n", (checkFoodName(foods, *foodCount, temp)) + 1);
                printf(">                         -- Enter a different name --                         <\n");
            }
        else
            strcpy(foods[i].name, temp);
    } while (checkFoodName(foods, *foodCount, temp) != -1);
    
    do {
        printf("--> Enter quantity: ");
        scanResult = scanf(" %f", &foods[i].quantity);

        if (scanResult != 1)
        {
            scanf(" %*s"); // removes bad input, prevents infinite loop when invalid
            foods[i].quantity = 0; //fix when character is inputted, quantity becomes 0 and loop continues to run but with invalid input
            printf("--> Invalid input. Please enter a number.\n>                              Please try again.                               <\n");            
        }
        else if (foods[i].quantity <= 0)
        {
            printf("!                          QTY can't be 0 or negative                          !\n>                              Please try again.                               <\n");
        }

    } while (scanResult != 1 || foods[i].quantity <= 0);

    printf("--> Enter unit: ");
    getString(foods[i].unit);
    do {
        printf("--> Enter calories: ");
        scanResult = scanf(" %f", &foods[i].calories);

        if (scanResult != 1)
        {
            scanf(" %*s"); // removes bad input, prevents infinite loop when invalid
            foods[i].calories = 0;
            printf("--> Invalid input. Please enter a number.\n>                              Please try again.                               <\n");
        }
        else if (foods[i].calories < 0)
        {
            printf("!                      Calories can't be negative                              !\n>                              Please try again.                               <\n");
        }
    } while (scanResult != 1 || foods[i].calories < 0);
    (*foodCount)++; // increment food count for next entry
    longDivider();
    printf("|>      --------       FOOD CALORIES ADDED SUCCESSFULLY!      --------        <|\n");
    longDivider();
}

/*
This function displays the food calorie entries in a page format, showing 10 entries at a time.
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - the number of food entries currently stored, used to determine how many entries to display and when to stop
    Pre-condition: there must be at least 1 food entry to display.
*/
char nextFoodEntry(int foodCount)
{
    (void)foodCount;
    char cChoice;

    printf("|>          Displaying next 10 entries. View more entries not shown?          <|\n");
    printf("|    Type 'N' to view next set of entries or 'X' to exit View Food Calories    |\n");
    printf("| %31s Choice: ", " ");
    while (cChoice != 'N' && cChoice != 'n' && cChoice != 'X' && cChoice != 'x')
    {
        scanf(" %c", &cChoice);
        if (cChoice != 'N' && cChoice != 'n' && cChoice != 'X' && cChoice != 'x')
        {
            printf("|    Invalid choice!  Please enter 'N' to view next set or 'X' to exit view    |\n");
            printf("| %31s Choice: ", " ");
        }
    }
    longDivider();

    return cChoice;
}

/*
This function displays the food calorie entries in a page format, showing 10 entries at a time.
    @param foods - array of foodTag structs where food calorie data is stored
    @param foodCount - the number of food entries currently stored, used to determine how many entries to display and when to stop
*/
void viewFoodCalories (struct foodTag foods[], int foodCount)
{
    int i;
    char cChoice;

    printf("\n");
    if (foodCount >=10 )
    {
        longDivider();
        printf("|>                        VIEWING FOOD CALORIES PAGE 1                        <|\n");
        printf("|          Food Item          |   Quantity   |     Unit     |     Calories     |\n");
        longDivider();

        for(i = 0; i < 9; i++)
        {
            printf("| %d. %24s | %12.2f | %12s | %16.2f |\n",
                i + 1, foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);
        }

        printf("| 10. %23s | %12.2f | %12s | %16.2f |\n",
                foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);

        if (foodCount <= 10)
        {
            printf("|>     ----------       VIEW FOOD CALORIE CHART SUCCESS!      ----------      <|\n");
            longDivider();
        }
            
        if (foodCount >=11)
        {
            printf("|>         Displaying first 10 entries. View more entries not shown?          <|\n");
            printf("|    Type 'N' to view next set of entries or 'X' to exit View Food Calories    |\n");
            printf("| %31s Choice: ", " ");
            while (cChoice != 'N' && cChoice != 'n' && cChoice != 'X' && cChoice != 'x')
            {
                scanf(" %c", &cChoice);
                if (cChoice != 'N' && cChoice != 'n' && cChoice != 'X' && cChoice != 'x')
                {
                    printf("|    Invalid choice!  Please enter 'N' to view next set or 'X' to exit view    |\n");
                    printf("| %31s Choice: ", " ");
                }
            }
            longDivider();

            switch (cChoice)
            {
                case 'N':
                case 'n':
                    longDivider();
                    printf("|>                        VIEWING FOOD CALORIES PAGE 2                        <|\n");
                    printf("|          Food Item          |   Quantity   |     Unit     |     Calories     |\n");
                    longDivider();

                    for(i = 10; i < 20 && i < foodCount; i++)
                    {
                        printf("| %d. %23s | %12.2f | %12s | %16.2f |\n",
                            i + 1, foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);
                    }

                    if (foodCount <= 20)
                    {
                        printf("|>     ----------       VIEW FOOD CALORIE CHART SUCCESS!      ----------      <|\n");
                        longDivider();
                    }

                    if (foodCount > 20)
                    {
                        longDivider();
                        cChoice = nextFoodEntry(foodCount);
                        switch (cChoice)
                        {
                            case 'N':
                            case 'n':
                                longDivider();
                                printf("|>                        VIEWING FOOD CALORIES PAGE 3                        <|\n");
                                printf("|          Food Item          |   Quantity   |     Unit     |     Calories     |\n");
                                longDivider();

                                for(i = 20; i < 30 && i < foodCount; i++)
                                {
                                    printf("| %d. %23s | %12.2f | %12s | %16.2f |\n",
                                        i + 1, foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);
                                }

                                if (foodCount <= 30)
                                {
                                    printf("|>     ----------       VIEW FOOD CALORIE CHART SUCCESS!      ----------      <|\n");
                                    longDivider();
                                }

                                if (foodCount > 30)
                                {
                                    longDivider();
                                    cChoice = nextFoodEntry(foodCount);
                                    switch (cChoice)
                                    {
                                        case 'N':
                                        case 'n':
                                            longDivider();
                                            printf("|>                        VIEWING FOOD CALORIES PAGE 4                        <|\n");
                                            printf("|          Food Item          |   Quantity   |     Unit     |     Calories     |\n");
                                            longDivider();

                                            for(i = 30; i < 40 && i < foodCount; i++)
                                            {
                                                printf("| %d. %23s | %12.2f | %12s | %16.2f |\n",
                                                    i + 1, foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);
                                            }

                                            if (foodCount <= 40)
                                            {
                                                printf("|>     ----------       VIEW FOOD CALORIE CHART SUCCESS!      ----------      <|\n");
                                                longDivider();
                                            }

                                            if (foodCount > 40)
                                            {
                                                longDivider();
                                                cChoice = nextFoodEntry(foodCount);
                                                switch (cChoice)
                                                {
                                                    case 'N':
                                                    case 'n':
                                                        longDivider();
                                                        printf("|>                        VIEWING FOOD CALORIES PAGE 5                        <|\n");
                                                        printf("|          Food Item          |   Quantity   |     Unit     |     Calories     |\n");
                                                        longDivider();

                                                        for(i = 40; i < foodCount; i++)
                                                        {
                                                            printf("| %d. %23s | %12.2f | %12s | %16.2f |\n",
                                                                i + 1, foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);
                                                        }
                                                        printf("|>     ----------       VIEW FOOD CALORIE CHART SUCCESS!      ----------      <|\n");
                                                        longDivider();
                                                    
                                                        break;
                                                    case 'X':
                                                    case 'x':
                                                        printf("|                        Exiting View Food Calories...                         |\n");
                                                        longDivider();
                                                        break;
                                                }
                                            }
                                            break;

                                        case 'X':
                                        case 'x':
                                            printf("|                        Exiting View Food Calories...                         |\n");
                                            longDivider();
                                            break;
                                    }
                                }
                                break;

                            case 'X':
                            case 'x':
                                printf("|                        Exiting View Food Calories...                         |\n");
                                longDivider();
                                break;
                        }
                    }
                    break;

                case 'X':
                case 'x':
                    printf("|                        Exiting View Food Calories...                         |\n");
                    longDivider();
                    break;
            }
        }
    }

    else if (foodCount == 0)
    {
        longDivider(); 
        printf("|>        ----------         NO FOOD CALORIE ENTRY!        ----------         <|\n");
        longDivider();
    }

    else
    {
        longDivider();
        printf("|>                        VIEWING FOOD CALORIES PAGE 1                        <|\n");
        printf("|          Food Item          |   Quantity   |     Unit     |     Calories     |\n");

        for(i = 0; i < foodCount; i++)
        {
            printf("| %d. %24s | %12.2f | %12s | %16.2f |\n",
                i + 1, foods[i].name, foods[i].quantity, foods[i].unit, foods[i].calories);
        }

        printf("|>     ----------       VIEW FOOD CALORIE CHART SUCCESS!      ----------      <|\n");
        longDivider();
    }
}

void saveCalories (struct foodTag foods[], int foodCount)
{
    FILE *sCal;
    int i;
    shortString filename;
    
    printf("\n>                           SAVING FOOD CALORIES...                            <\n");
    longDivider2();
    printf("--> Enter filename to save: ");
    printf("\n--> ");
    getString(filename);

    sCal = fopen(filename,"w");

    for(i=0;i<foodCount;i++)
    {
        fprintf(sCal, "%s\n", foods[i].name);
        fprintf(sCal, "%.2f %s %.2f\n\n", foods[i].quantity, foods[i].unit, foods[i].calories);
    }

    fclose(sCal);

    longDivider();
    printf("|>       --------       FOOD CALORIES SAVED SUCCESSFULLY!       --------       <|\n");
    longDivider();
    printf("\n");
}

void loadCalories(struct foodTag foods[], int *foodCount)
{
   FILE *lCal;
   shortString filename;
   int existingIndex;
   char overwriteChoice;

    printf("\n>                           LOADING FOOD CALORIES...                           <\n");
    longDivider2();
    printf("--> Enter filename to load: ");
    printf("\n--> ");
    getString(filename);

    lCal = fopen(filename,"r");

    if(lCal == NULL)
    {
        printf("!           File not found. Please check the filename and try again.           !\n");
        longDivider2();
    }
    else
    {
        while (*foodCount < 50 && fscanf(lCal, " %20[^\n]", foods[*foodCount].name)==1)
        {
            fscanf(lCal, "%*c");  // consume the \n after name
    
            // Read qty, unit, calories directly to struct fields
            fscanf(lCal, " %f %20s %f", &foods[*foodCount].quantity, 
                                         foods[*foodCount].unit, 
                                         &foods[*foodCount].calories);
                
            fscanf(lCal, "%*c");  // consume the \n after data
            fscanf(lCal, "%*c");  // consume blank line \n
                
            // Check for duplicates
            existingIndex = checkFoodName(foods, *foodCount, foods[*foodCount].name);
                
            if (existingIndex != -1)  // food name already exists
            {
                printf("\n! Food '%s' already exists at entry #%d !\n", foods[*foodCount].name, existingIndex + 1);
                printf("--> Overwrite existing data? (Y/N): ");
                    
                overwriteChoice = '\0';
                while (overwriteChoice != 'Y' && overwriteChoice != 'y' && overwriteChoice != 'N' && overwriteChoice != 'n')
                {
                    scanf(" %c", &overwriteChoice);
                }
                
                if (overwriteChoice == 'Y' || overwriteChoice == 'y')
                {
                    foods[existingIndex].quantity = foods[*foodCount].quantity;
                    strcpy(foods[existingIndex].unit, foods[*foodCount].unit);
                    foods[existingIndex].calories = foods[*foodCount].calories;
                    printf("== Entry #%d overwritten successfully! ==\n", existingIndex + 1);
                }
                else
                        printf("== Keeping existing entry #%d. Loaded entry skipped. ==\n", existingIndex + 1);
            }
            else  // food name does not exist, add new entry
            {
                (*foodCount)++;
                printf("== Food '%s' loaded successfully! ==\n", foods[*foodCount - 1].name);
            }
        }
        fclose(lCal);
    }
}

/*
This function allows the user to add a new recipe entry.
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - pointer to the integer that keeps track of how many recipe entries are currently stored, used to determine where to add the new entry and to increment after adding
    Pre-condition: the user must input a unique recipe title that does not already exist in the array, 
    and must input valid values for servings (servings > 0), at least 1 ingredient, and at least 1 step.
*/
void addRecipe (struct recipeTag recipes[], int *recipeCount)
{
    int count = 0;
    int stepCount = 0;
    int doneIngredients = 0;
    int doneSteps = 0;
    int scanResult;
    shortString temp;

    longDivider();
    printf("|>                            ADDING NEW RECIPE...                            <|\n");
    longDivider();

    do {
        printf("--> Enter recipe title: ");
        getString(temp);

        if (checkRecipeTitle(recipes, *recipeCount, temp) != -1)
        {
            printf("!                         Recipe exists // View Number %d                       !\n", (checkRecipeTitle(recipes, *recipeCount, temp)) + 1);
            printf(">                         -- Enter a different name --                         <\n");
        }
        else
            strcpy(recipes[*recipeCount].title, temp);
    } while (checkRecipeTitle(recipes, *recipeCount, temp) != -1);
    
    printf("--> Enter recipe classification: ");
    getString(recipes[*recipeCount].classification);
    if (caseInsensitiveCompare(recipes[*recipeCount].classification, "starter") != 0 && caseInsensitiveCompare(recipes[*recipeCount].classification, "main") != 0 && caseInsensitiveCompare(recipes[*recipeCount].classification, "dessert") != 0)
    {
        do {
            printf("!     Invalid classification. Please enter 'starter', 'main', or 'dessert'.    !\n");
            printf("--> Enter recipe classification: ");
            getString(recipes[*recipeCount].classification);
        } while (caseInsensitiveCompare(recipes[*recipeCount].classification, "starter") != 0 && caseInsensitiveCompare(recipes[*recipeCount].classification, "main") != 0 && caseInsensitiveCompare(recipes[*recipeCount].classification, "dessert") != 0);
    }
    
    do {
        printf("--> Enter number of servings: ");
        scanResult = scanf(" %d", &recipes[*recipeCount].servings);

        if (scanResult != 1)
        {
            scanf(" %*s"); // removes bad input, prevents infinite loop when invalid
            recipes[*recipeCount].servings = 0; //fix when character is inputted, quantity becomes 0 and loop continues to run but with invalid input
            printf("--> Invalid input. Please enter a number.\n>                              Please try again.                               <\n");            
        }
        else if (recipes[*recipeCount].servings <= 0)
        {
            printf("!                          QTY can't be 0 or negative                          !\n>                              Please try again.                               <\n");
        }

    } while (scanResult != 1 || recipes[*recipeCount].servings <= 0);

    printf("--> Enter ingredients (type 'done' when finished): \n");
    while (count < 20 && !doneIngredients)
    {
        printf("--> Ingredient %d name: ", count + 1);
        getString(recipes[*recipeCount].ingredients[count].item);

        if (caseInsensitiveCompare(recipes[*recipeCount].ingredients[count].item, "done") == 0)
        {
            if (count == 0)
            {
                printf("|>        ----------   At least 1 ingredient is required!   ----------        <|\n");
                longDivider();
            }
            else
                doneIngredients = 1;
        }

        else
        {
            do {
                printf("--> Ingredient %d quantity: ", count + 1);
                scanResult = scanf(" %f", &recipes[*recipeCount].ingredients[count].quantity);

                if (scanResult != 1)
                {
                    scanf(" %*s"); // removes bad input, prevents infinite loop when invalid
                    recipes[*recipeCount].ingredients[count].quantity = 0.0f; //fix when character is inputted, quantity becomes 0 and loop continues to run but with invalid input
                    printf("--> Invalid input. Please enter a number.\n>                              Please try again.                               <\n");            
                }
                else if (recipes[*recipeCount].ingredients[count].quantity <= 0)
                {
                    printf("!                          QTY can't be 0 or negative                          !\n>                              Please try again.                               <\n");
                }
            } while (scanResult != 1 || recipes[*recipeCount].ingredients[count].quantity <= 0);

            printf("--> Ingredient %d unit: ", count + 1);
            getString(recipes[*recipeCount].ingredients[count].unit);
            count++;
        }
    }
    recipes[*recipeCount].ingredientCount = count;

    printf("--> Enter steps (type 'done' when finished): \n");

    while (stepCount < 15 && !doneSteps) {
        printf("--> Step %d: ", stepCount + 1);
        getString(recipes[*recipeCount].steps[stepCount]);

        if (caseInsensitiveCompare(recipes[*recipeCount].steps[stepCount], "done") == 0)
        {
            if (stepCount == 0)
            {
                printf("|>          ----------   At least 1 step is required!    ----------           <|\n");
                longDivider();
            }
            else
                doneSteps = 1;
        }

        else
            stepCount++;
    }
    recipes[*recipeCount].stepCount = stepCount;
    (*recipeCount)++;
}

/*
This function checks if an ingredient already exists in a recipe's ingredient list.
    @param ingredient - the name of the ingredient to check
    @param recipes - array of recipeTag structs where recipe data is stored
    @param nIndex - the index of the recipe in the array to check for the ingredient
    @return - the index of the existing ingredient if found, otherwise -1
    Pre-condition: the recipe at nIndex must exist, and the ingredient name must be valid (not empty or null)
*/
int checkIngredient (shortString ingredient, struct recipeTag recipes[], int nIndex)
{
    int res = -1;
    int i;

    for (i = 0; i < recipes[nIndex].ingredientCount; i++)
    {
        if (caseInsensitiveCompare(recipes[nIndex].ingredients[i].item, ingredient) == 0)
            res = i;
    }
    return res; 
}

/*
This function deletes an ingredient from a recipe's ingredient list and shifts the remaining ingredients up to fill the gap.
    @param ingredient - the name of the ingredient to delete
    @param recipes - array of recipeTag structs where recipe data is stored
    @param nIndex - the index of the recipe in the array to delete the ingredient from
    Pre-condition: Cannot delete if there is only 1 ingredient
*/
void deleteIngredient (shortString ingredient, struct recipeTag recipes[], int nIndex)
{
    int i;
    int ingredientIndex = checkIngredient(ingredient, recipes, nIndex);
    int lastIngredient = recipes[nIndex].ingredientCount;

    if (ingredientIndex != -1)
    {
        for (i = ingredientIndex; i < lastIngredient-1; i++)
        { // shift ingredients  
            recipes[nIndex].ingredients[i] = recipes[nIndex].ingredients[i + 1];
        }
        
        // delete all info
        recipes[nIndex].ingredients[lastIngredient - 1].item[0] = '\0';
        recipes[nIndex].ingredients[lastIngredient - 1].quantity = 0.0f;
        recipes[nIndex].ingredients[lastIngredient - 1].unit[0] = '\0';
        recipes[nIndex].ingredientCount--;
    }

    else
    {
        printf("|>      ----------         INGREDIENT NOT FOUND!         ----------        <|\n");
        longDivider();
    }
}

/*
This function displays the list of ingredients for a specific recipe in a formatted table.
    @param recipes - array of recipeTag structs where recipe data is stored
    @param nIndex - the index of the recipe in the array to display the ingredients for
*/
void listIngredients (struct recipeTag recipes[], int nIndex)
{
    int i;

    longDivider();
    printf("|>       ----------       LIST OF EXISTING INGREDIENTS       ----------       <|\n");
    longDivider();
    printf("|          Ingredient Name            |     Quantity     |        Unit         |\n");
    longDivider();

    for (i = 0; i < recipes[nIndex].ingredientCount; i++)
    {
        printf("| %d. %32s | %16.2f | %19s |\n",
            i + 1, recipes[nIndex].ingredients[i].item, recipes[nIndex].ingredients[i].quantity, recipes[nIndex].ingredients[i].unit);
    }
}

/*
This function displays the list of steps for a specific recipe in a formatted table.
    @param recipes - array of recipeTag structs where recipe data is stored
    @param nIndex - the index of the recipe in the array to display the steps for
*/
void listSteps (struct recipeTag recipes[], int nIndex)
{
    int i;

    longDivider();
    printf("|>         ----------         LIST OF EXISTING STEPS         ----------       <|\n");
    longDivider();

    for (i = 0; i < recipes[nIndex].stepCount; i++)
    {
        printf("| %d. %73s |\n", i + 1, recipes[nIndex].steps[i]);
    }
}

/*
This function deletes a step from a recipe's step list and shifts the remaining steps up to fill the gap.
    @param nStep - the index of the step to delete (1-based index for user input)
    @param recipes - array of recipeTag structs where recipe data is stored
    @param nIndex - the index of the recipe in the array to delete the step from
    Pre-condition: Cannot delete if there is only 1 step
*/
void deleteStep (int nStep, struct recipeTag recipes[], int nIndex)
{
    int i;
    int lastStep = recipes[nIndex].stepCount;

    for (i = nStep - 1; i < lastStep - 1; i++)
    { // shift steps
        strcpy(recipes[nIndex].steps[i], recipes[nIndex].steps[i + 1]);
    }

    // delete last step info
    recipes[nIndex].steps[lastStep - 1][0] = '\0';
    recipes[nIndex].stepCount--;
}

/*
This function allows the user to modify an existing recipe by adding or deleting ingredients and steps.
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - the number of recipe entries currently stored, used to check if there are recipes to modify and to validate user input for selecting a recipe
    Pre-condition: there must be at least 1 recipe entry to modify, and the user must input a valid recipe title that exists in the array when prompted.
*/
void modifyRecipe (struct recipeTag recipes[], int recipeCount)
{
    shortString tempTitle, tempIngredient;
    int cOpt = -1;
    int index;
    int ingredientCount, stepCount, nStep; //nstep index of step to be deleted
    int scanResult;

    if (recipeCount == 0)
    {
        printf("\n");
        longDivider();
        printf("|>      ----------           NO FOOD RECIPES FOUND!          ----------       <|\n");
        printf("|>      --------            RETURNING TO UPDATE MENU           --------        |\n");
        longDivider();
    }
    
    else
    {
        listRecipe(recipes, recipeCount);
        printf("\n");
        longDivider();
        printf("--> Enter recipe title to be modified: ");
        getString(tempTitle);

        while (checkRecipeTitle(recipes, recipeCount, tempTitle) == -1)
        {
            printf("|>        ----------           RECIPE NOT FOUND!           ----------         <|\n");
            longDivider();
            printf("--> Enter recipe title to be modified: ");
            getString(tempTitle);
        }

        index = checkRecipeTitle(recipes, recipeCount, tempTitle);
        do
        {
            longDivider();
            printf("\n|>       ----------       RECIPE FOUND SUCCESSFULLY!       ----------         <|\n");
            longDivider();
            printf("|>                       CHOOSE MODIFICATION OPTION.                          <|\n");
            printf("|>               [1] Add Ingredient    [2] Delete Ingredient                  <|\n");
            printf("|>                  [3] Add Step          [4] Delete Step                     <|\n");
            printf("|>                  [5] Return to Update Recipe Box Menu                      <|\n");
            printf("| Option: ");
            scanf(" %d", &cOpt);

            while (cOpt < 1 || cOpt > 5)
            {
                printf("|>         Invalid option! Please enter a valid modification option.          <|\n");
                printf("| Option: ");
                scanf(" %d", &cOpt);
            }

            longDivider();
            printf("\n");

            switch (cOpt)
            {
            case 1:
                ingredientCount = recipes[index].ingredientCount;

                if (ingredientCount >= 20)
                {
                    printf("|>      ----------         INGREDIENT LIST IS FULL!         ----------        <|\n");
                    longDivider();
                }

                else
                {
                    listIngredients(recipes, index);
                    printf("|                            ADDING NEW INGREDIENT                             |\n");
                    longDivider();
                    printf("--> Enter ingredient name: ");
                    getString(recipes[index].ingredients[ingredientCount].item);
                    printf("--> Enter ingredient quantity: ");
                    scanf(" %f", &recipes[index].ingredients[ingredientCount].quantity);
                    printf("--> Enter ingredient unit: ");
                    getString(recipes[index].ingredients[ingredientCount].unit);

                    if (ingredientCount + 1 < 20)
                        strcpy(recipes[index].ingredients[ingredientCount + 1].item, "done");
                    
                    recipes[index].ingredientCount++;

                    printf("|>      ----------       INGREDIENT ADDED SUCCESSFULLY!       ----------      <|\n");
                    listIngredients(recipes, index);
                    longDivider();
                }
                break;

            case 2:
                ingredientCount = recipes[index].ingredientCount;

                if (ingredientCount == 0)
                {
                    printf("|>      ----------         NO INGREDIENTS TO DELETE!        ----------        <|\n");
                    longDivider();
                }
                else if (ingredientCount == 1)
                {
                    listIngredients(recipes, index);
                    printf("|>      ----------      CANNOT DELETE THE LAST INGREDIENT     ----------      <|\n");
                    longDivider();
                }

                else
                {
                    listIngredients(recipes, index);
                    printf("|                            DELETING AN INGREDIENT                            |\n");
                    printf("--> Enter ingredient name to delete: ");
                    getString(tempIngredient);

                    if (checkIngredient(tempIngredient, recipes, index) == -1)
                    {
                        do {
                            printf("|>        ----------          INGREDIENT NOT FOUND!         ----------        <|\n");
                            longDivider();
                            printf("--> Enter ingredient name to delete: ");
                            getString(tempIngredient);
                        } while (checkIngredient(tempIngredient, recipes, index) == -1);
                    }

                    deleteIngredient(tempIngredient, recipes, index);
                    printf("|>     ----------       INGREDIENT DELETED SUCCESSFULLY!       ----------     <|\n");
                    listIngredients(recipes, index);
                    longDivider();
                }
                break;

            case 3:
                stepCount = recipes[index].stepCount;

                if (stepCount == 15)
                {
                    printf("|>      ----------           STEP COUNT IS FULL!           ----------        <|\n");
                    longDivider();
                }

                else
                {
                    listSteps(recipes, index);
                    printf("|                                ADDING NEW STEP                               |\n");
                    longDivider();
                    printf("--> Enter step: ");
                    getString(recipes[index].steps[stepCount]);
                    recipes[index].stepCount++;
                    printf("|>        ----------        STEP ADDED SUCCESSFULLY!       ----------        <|\n");
                    listSteps(recipes, index);
                    longDivider();
                }
                break;

            case 4:
                stepCount = recipes[index].stepCount;

                if (stepCount == 0)
                {
                    printf("|>       ----------           NO STEPS TO DELETE!          ----------         <|\n");
                    longDivider();
                }
                else if (stepCount == 1)
                {
                    listSteps(recipes, index);
                    printf("|>       ----------        CANNOT DELETE THE LAST STEP!       ----------      <|\n");
                    longDivider();
                }

                else
                {
                    listSteps(recipes, index);
                    printf("|                               DELETING A STEP                                |\n");

                    do {
                        printf("--> Enter the step number to delete: ");
                        scanResult = scanf(" %d", &nStep);

                        if (scanResult != 1)
                        {
                            scanf(" %*s");
                            nStep = 0;
                        }

                        if (scanResult != 1 || nStep < 1 || nStep > stepCount)
                        {
                            printf("|>         ----------          INVALID STEP NUMBER!         ----------        <|\n");
                            longDivider();
                        }
                    } while (scanResult != 1 || nStep < 1 || nStep > stepCount);

                    deleteStep(nStep, recipes, index);
                    printf("|>        ----------       STEP DELETED SUCCESSFULLY!       ----------        <|\n");
                    listSteps(recipes, index);
                    longDivider();
                }
                break;

            case 5:
                printf("|>      --------          RETURNING TO UPDATE MENU...         --------        <|\n");
                longDivider();
                break;
            }
        } while (cOpt != 5);

    }
}

void sortRecipes (struct recipeTag recipes[], int recipeCount)
{
    int x, y, min;
    struct recipeTag tempStruct; 

    for(x = 0; x < recipeCount - 1; x++)
    {
        min = x;
        for(y = x + 1; y < recipeCount; y++)
        {
            if(caseInsensitiveCompare(recipes[y].title, recipes[min].title) < 0)
                min = y;
        }
        if(min != x)
        {
            tempStruct = recipes[x];
            recipes[x] = recipes[min];
            recipes[min] = tempStruct;
        }
    }
}

void listRecipe (struct recipeTag recipes[], int recipeCount)
{
    sortRecipes(recipes, recipeCount);
    int i;

    printf("\n");
    if (recipeCount == 0)
    {
        longDivider();
        printf("|>       ----------          NO FOOD RECIPES FOUND!          ----------       <|\n");
        longDivider();
    }
    else
    {
        longDivider();
        printf("|>                           LIST OF FOOD RECIPES                             <|\n");
        printf("|             Recipe Title             |   Classification   |     Servings     |\n");
        longDivider();

        for(i = 0; i < recipeCount; i++)
        {
            printf("| %-2d. %32s | %18s | %16d |\n",
                i + 1, recipes[i].title, recipes[i].classification, recipes[i].servings);
        }

        printf("|>      ----------       LIST OF FOOD RECIPES SUCCESS!      ----------        <|\n");
        longDivider();
        printf("\n");
    }
}

void deleteRecipe (struct recipeTag recipes[], int *recipeCount)
{
    shortString tempTitle;
    int i,index;

    printf("\n");
    longDivider();
    printf("|>                            DELETING A RECIPE...                            <|\n");
    longDivider();
    
    if(*recipeCount > 0)
    {
        listRecipe(recipes, *recipeCount);
        printf("--> Enter recipe title to delete: ");
        getString(tempTitle);
    }
    
    if(checkRecipeTitle(recipes, *recipeCount, tempTitle) == -1)
    {
        printf("|>        ----------           RECIPE NOT FOUND!           ----------         <|\n");
        longDivider();
    }
    else
    {
        index = checkRecipeTitle(recipes, *recipeCount, tempTitle);
        for(i = index; i < *recipeCount - 1; i++)
        {
            recipes[i] = recipes[i + 1]; // shift recipes down to overwrite deleted recipe
        }
        (*recipeCount)--; // decrement recipe count
        printf("|>      ----------       RECIPE DELETED SUCCESSFULLY!       ----------        <|\n");
        longDivider();
    }

}

/*
This function retrieves the calorie information for a given ingredient by searching through the food entries.
    @param ingredientName - the name of the ingredient to search for
    @param foods - array of foodTag structs where food data is stored
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through
    @return - the calorie value of the ingredient if found, otherwise returns 0.0f
    Pre-condition: the ingredientName must be valid (not empty or null), and the foods array must be properly populated with valid food entries.
*/
float getIngredientCalories(const char *ingredientName, struct foodTag foods[], int foodCount)
{
    int i;
    float calories = 0.0f;
    int found = 0;

    for (i = 0; i < foodCount && found == 0; i++)
    {
        if (foods[i].name[0] != '\0' && caseInsensitiveCompare(ingredientName, foods[i].name) == 0)
        {
            calories = foods[i].calories;
            found = 1;
        }
    }

    return calories;
}

/*
This function calculates the total calories for a given recipe by summing up the calories of all its ingredients.
    @param recipe - the recipe for which to calculate calories
    @param foods - array of foodTag structs where food data is stored
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through
    @return - the total calorie value of the recipe if found, otherwise returns 0.0f
    Pre-condition: the recipe must be valid (not empty or null), and the foods array must be properly populated with valid food entries.
*/
float calculateRecipeCalories(struct recipeTag recipe, struct foodTag foods[], int foodCount)
{
    float totalCalories = 0.0f;
    int j;
    float baseCalories, ingredientCalories;

    for (j = 0; j < 20 && recipe.ingredients[j].item[0] != '\0' && caseInsensitiveCompare(recipe.ingredients[j].item, "done") != 0; j++)
    {
        baseCalories = getIngredientCalories(recipe.ingredients[j].item, foods, foodCount);
        ingredientCalories = baseCalories * recipe.ingredients[j].quantity;
        totalCalories += ingredientCalories;
    }
    return totalCalories;
}

/*
This function displays the details of a given recipe, including its ingredients and procedures.
    @param recipe - the recipe to display
    @param foods - array of foodTag structs where food data is stored
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through
    Pre-condition: the recipe must be valid (not empty or null), and the foods array must be properly populated with valid food entries.
*/
void displayRecipe(struct recipeTag recipe, struct foodTag foods[], int foodCount)
{
    int j, k;
    float baseCalories, ingredientCalories;
    float totalCalories = 0.0f;

    totalCalories = calculateRecipeCalories(recipe, foods, foodCount);

    longDivider();
    printf("| Recipe Title: %-20s Servings: %-6d Total Calories: %-8.2f |\n", recipe.title, recipe.servings, totalCalories);
    printf("| Ingredients: %63s |\n", " ");
    printf("| Quantity     | Unit            | Food Item                    | Calories     |\n");

    for (j = 0; j < 20 && recipe.ingredients[j].item[0] != '\0' && caseInsensitiveCompare(recipe.ingredients[j].item, "done") != 0; j++)
    {
        baseCalories = getIngredientCalories(recipe.ingredients[j].item, foods, foodCount);
        ingredientCalories = baseCalories * recipe.ingredients[j].quantity;
        printf("| %-12.2f | %-15s | %-28s | %-12.2f |\n",
            recipe.ingredients[j].quantity, recipe.ingredients[j].unit, recipe.ingredients[j].item, ingredientCalories);
    }

    printf("| Procedures: %64s |\n", " ");
    for (k = 0; k < 15 && recipe.steps[k][0] != '\0' && caseInsensitiveCompare(recipe.steps[k], "done") != 0; k++)
    {
        printf("| Step %d: %68s |\n", k + 1, recipe.steps[k]);
    }

    longDivider();
}

/*
This function allows the user to view the details of each recipe entry one by one, with the option to navigate to the next recipe or exit the scan.
    @param recipes - array of recipeTag structs where recipe data is stored
    @param recipeCount - the number of recipe entries currently stored, used to determine how many entries to display and to validate navigation through the recipes
    @param foods - array of foodTag structs where food data is stored, used to retrieve calorie information for the ingredients in the recipes
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through for calorie information
    Pre-condition: there must be at least 1 recipe entry to view, and the user must input valid navigation choices ('N' for next, 'X' for exit) when prompted.
*/
void scanRecipe (struct recipeTag recipes[], int recipeCount, struct foodTag foods[], int foodCount)
{
    int i = 0;
    int exitScan = 0;
    int canPrev; // para maindetify kung pwede magprev or next, para mahandle yung first and last recipe cases
    int canNext;
    char cChoice;

    printf("\n");
    if (recipeCount == 0)
    {
        longDivider();
        printf("|>         ----------          RECIPES NOT FOUND!        ----------           <|\n");
        longDivider();
    }

    //arrange in alphabetical order
    sortRecipes(recipes, recipeCount);
    
    while (i < recipeCount && exitScan == 0)
    {
        canPrev = (i > 0);
        canNext = (i < recipeCount - 1);

        printf("  Displaying %d out of %d recipes.\n", i + 1, recipeCount);

        displayRecipe(recipes[i], foods, foodCount);

        longDivider();
        if (canPrev && canNext)
            printf("|     Type 'P' for previous, 'N' for next recipe, or 'X' to exit Scan Recipe   |");
        else if (canNext)
            printf("|           Type 'N' to view next recipe or 'X' to exit Scan Recipe            |");
        else if (canPrev)
            printf("|         Type 'P' to view previous recipe or 'X' to exit Scan Recipe          |");
        else
            printf("|                      Type 'X' to exit Scan Recipe only                       |");

        printf("\n| %31s Choice: ", " ");
        scanf(" %c", &cChoice);

        while (!(cChoice == 'X' || cChoice == 'x' ||
                (canNext && (cChoice == 'N' || cChoice == 'n')) ||
                (canPrev && (cChoice == 'P' || cChoice == 'p'))))
        {
            if (canPrev && canNext)
                printf("|              Invalid choice! Please enter 'P', 'N', or 'X' only               |\n");
            else if (canNext)
                printf("|                 Invalid choice! Please enter 'N' or 'X' only                  |\n");
            else if (canPrev)
                printf("|                 Invalid choice! Please enter 'P' or 'X' only                  |\n");
            else
                printf("|                    Invalid choice! Please enter 'X' only                      |\n");

            printf("| %31s Choice: ", " ");
            scanf(" %c", &cChoice);
        }

        if (cChoice == 'X' || cChoice == 'x')
        {
            exitScan = 1;
            longDivider();
        }
        else if (canNext && (cChoice == 'N' || cChoice == 'n'))
        {
            longDivider();
            printf("\n");
            i++;
        }
        else if (canPrev && (cChoice == 'P' || cChoice == 'p'))
        {
            longDivider();
            printf("\n");
            i--;
        }
    }
    printf("\n");
}

void searchRecipe (struct recipeTag recipes[], int recipeCount)
{
    shortString tempTitle;
    int check;
    int i,j;

    listRecipe(recipes, recipeCount);
    if (recipeCount != 0)
    {
        printf("--> Enter recipe title to search: ");
        getString(tempTitle);
        check = checkRecipeTitle(recipes, recipeCount, tempTitle);

        if (check == -1)
        {
            longDivider();
            printf("|>        ----------           RECIPE NOT FOUND!           ----------         <|\n");
            longDivider();
        }
        else
        {
            longDivider();
            printf("|>       ----------       RECIPE FOUND SUCCESSFULLY!       ----------         <|\n");
            longDivider();
            printf("| Recipe Title: %-20s Servings: %-5d Classification: %-9s |\n", recipes[check].title, recipes[check].servings, recipes[check].classification);
            longDivider();
            printf("| Ingredients: %d %61s |\n", recipes[check].ingredientCount, " ");
            printf("|          Food Item          |      Quantity       |           Unit           |\n");

            for (i = 0; i < recipes[check].ingredientCount; i++)
            {
                printf("| %-27s | %-19.2f | %-24s |\n",
                    recipes[check].ingredients[i].item, recipes[check].ingredients[i].quantity, recipes[check].ingredients[i].unit);
            }
            longDivider();
            printf("| Steps: %d %67s |\n", recipes[check].stepCount, " ");
            for (j = 0; j < recipes[check].stepCount; j++)
            {
                printf("| Step %d: %68s |\n", j + 1, recipes[check].steps[j]);
            }

            longDivider();
        }
    }
}

void exportRecipe (struct recipeTag recipes[], int recipeCount)
{
    FILE *eRec;
    int i;
    shortString filename;
    
    printf("\n>                             EXPORTING RECIPES...                             <\n");
    longDivider2();
    printf("--> Enter filename to export (with .txt): ");
    printf("\n--> ");
    getString(filename);
    
    eRec = fopen(filename,"w");

    if(eRec == NULL)
    {
        printf("!                                File not found                                !\n");
        longDivider2();
        fclose(eRec);
    }
    else
    {
        for(i=0;i<recipeCount;i++)
        {
            fprintf(eRec, "%s\n", recipes[i].title);
            fprintf(eRec, "%d %s\n", recipes[i].servings, recipes[i].classification);
            fprintf(eRec, "Ingredients %d\n", recipes[i].ingredientCount);
            for (int j = 0; j < recipes[i].ingredientCount; j++)
            {
                fprintf(eRec, "%.2f %s %s\n", recipes[i].ingredients[j].quantity, 
                                                recipes[i].ingredients[j].unit, 
                                                recipes[i].ingredients[j].item);
            }
            fprintf(eRec, "Steps %d\n", recipes[i].stepCount);
            for (int j = 0; j < recipes[i].stepCount; j++)
            {
                fprintf(eRec, "%s\n", recipes[i].steps[j]);
            }
            fprintf(eRec, "\n");
        }

        fclose(eRec);
    }
}

void importRecipe (struct recipeTag recipes[], int *recipeCount)
{
   FILE *iRec;
   shortString filename;
   int i,j;
   int existingIndex;
   char overwriteChoice;
   char trash[20]; // buffer for reading lines

    printf("\n>                             IMPORTING RECIPES...                             <\n");
    longDivider2();
    printf("--> Enter filename to import (with .txt): ");
    printf("\n--> ");
    getString(filename);

    iRec = fopen(filename,"r");

    if(iRec == NULL)
    {
        printf("!                                File not found                                !\n");
        longDivider2();
    }
    else
    {      
        while (*recipeCount < 50 && fscanf(iRec, " %20[^\n]", recipes[*recipeCount].title)==1)
        {
            i  = *recipeCount;

            fscanf(iRec, "%*c");

            fscanf(iRec, " %d %20[^\n]", &recipes[i].servings, recipes[i].classification);
            fscanf(iRec, "%*c");

            fscanf(iRec, " %20s %d", trash, &recipes[i].ingredientCount);
            fscanf(iRec, "%*c");

            for(j = 0; j < recipes[i].ingredientCount; j++)
            {
                fscanf(iRec, " %f %20s %20[^\n]",
                    &recipes[i].ingredients[j].quantity,
                    recipes[i].ingredients[j].unit,
                    recipes[i].ingredients[j].item);
                fscanf(iRec, "%*c");
            }

            fscanf(iRec, " %20s %d", trash, &recipes[i].stepCount);
            fscanf(iRec, "%*c");

            for(j = 0; j < recipes[i].stepCount; j++)
            {
                fscanf(iRec, " %20[^\n]", recipes[i].steps[j]);
                fscanf(iRec, "%*c");
            }

            fscanf(iRec, "%*c");

            // Check for duplicates
            existingIndex = checkRecipeTitle(recipes, *recipeCount, recipes[*recipeCount].title);
                
            if (existingIndex != -1)  // recipe title already exists
            {
                printf("\n! Recipe '%s' already exists at entry #%d !\n", recipes[*recipeCount].title, existingIndex + 1);
                printf("--> Overwrite existing data? (Y/N): ");
                    
                overwriteChoice = '\0';
                while (overwriteChoice != 'Y' && overwriteChoice != 'y' && overwriteChoice != 'N' && overwriteChoice != 'n')
                {
                    scanf(" %c", &overwriteChoice);
                }
                
                if (overwriteChoice == 'Y' || overwriteChoice == 'y')
                {
                    
                    recipes[existingIndex].servings = recipes[*recipeCount].servings;
                    strcpy(recipes[existingIndex].classification, recipes[*recipeCount].classification);
                    recipes[existingIndex].ingredientCount = recipes[*recipeCount].ingredientCount;
                    for (i = 0; i < recipes[*recipeCount].ingredientCount; i++)
                    {
                        recipes[existingIndex].ingredients[i] = recipes[*recipeCount].ingredients[i];
                    }
                    recipes[existingIndex].stepCount = recipes[*recipeCount].stepCount;
                    for (i = 0; i < recipes[*recipeCount].stepCount; i++)
                    {
                        strcpy(recipes[existingIndex].steps[i], recipes[*recipeCount].steps[i]);
                    }
                    printf("== Entry #%d overwritten successfully! ==\n", existingIndex + 1);
                }
                else
                        printf("== Keeping existing entry #%d. Loaded entry skipped. ==\n", existingIndex + 1);
            }
            else  // recipe title does not exist, add new entry
            {
                (*recipeCount)++;
                printf("== Recipe '%s' loaded successfully! ==\n", recipes[*recipeCount - 1].title);
            }
        }
        fclose(iRec);
    }
}

void generateShoppingList (struct recipeTag recipes[], int recipeCount)
{
    shortString tempTitle;
    int i;
    int check;
    int servingSize;
    float ratio;

    listRecipe(recipes, recipeCount);
    if(recipeCount != 0)
    {
        printf("--> Enter recipe title to generate shopping list: ");
        getString(tempTitle);
        check = checkRecipeTitle(recipes, recipeCount, tempTitle);
        if(check == -1)
        {
            longDivider();
            printf("|>        ----------           RECIPE NOT FOUND!           ----------         <|\n");
            longDivider();
        }
        else
        {
            printf("\n");
            printf("For how many people are you planning to cook this recipe for?:");
            scanf("%d", &servingSize);
            ratio = (float)servingSize / recipes[check].servings;

            printf("\n");
            longDivider();
            printf("|>        ----------            SHOPPING LIST!             ----------         <|\n");
            longDivider();
            printf("| Recipe Title: %-62s |\n", recipes[check].title);
            printf("| Serving Size: %-62d |\n", servingSize);
            longDivider();
            printf("| Ingredients: %d %61s |\n", recipes[check].ingredientCount, " ");
            printf("|          Food Item          |      Quantity       |           Unit           |\n");

            for (i = 0; i < recipes[check].ingredientCount; i++)
            {
                printf("| %-27s | %-19.2f | %-24s |\n",
                    recipes[check].ingredients[i].item, recipes[check].ingredients[i].quantity * ratio, recipes[check].ingredients[i].unit);
            }
            printf("|>         ----------       END OF SHOPPING LIST!        ----------           <|\n");
            longDivider();
        }
    }
}

void scanIngredient (struct recipeTag recipes[], int recipeCount, struct foodTag foods[], int foodCount)
{
    int i, j;
    shortString tempIngredient;
    struct recipeTag tempRecipes[50];
    int tempRecipeCount = 0;

    if(recipeCount == 0)
    {
        longDivider();
        printf("|>        ----------           NO RECIPES FOUND!           ----------         <|\n");
        longDivider();
    }
    else
    {
        printf("--> Enter ingredient name to scan: ");
        getString(tempIngredient);

        for (i = 0; i < recipeCount; i++)
        {
            for (j = 0; j < recipes[i].ingredientCount; j++)
            {
                if (caseInsensitiveCompare(recipes[i].ingredients[j].item, tempIngredient) == 0)
                {
                    tempRecipes[tempRecipeCount] = recipes[i];
                    tempRecipeCount++;
                }
            }
        }

        if(tempRecipeCount == 0)
        {
            longDivider();
            printf("|>        ----------          INGREDIENT NOT FOUND!         ----------        <|\n");
            longDivider();
        }
        else
        {
            longDivider();
            printf("|>       ----------       RECIPES WITH '%s' FOUND!       ----------         <|\n", tempIngredient);
            longDivider();
            scanRecipe(tempRecipes, tempRecipeCount, foods, foodCount); // pass the foods array and its count
        }
    }

}

/*
This function displays the recommended main course recipe based on the user's target calorie intake
    @param mainRecipes - array of indices for recipes classified as "main" in the recipes array
    @param starterCount - the number of starter recipes available, used to determine if there are valid starter options to consider for calorie calculations
    @param mainIndex - the index of the recommended main course recipe in the recipes array, used to retrieve and display the recipe details
    @param recipes - array of recipeTag structs where recipe data is stored, used to retrieve recipe details for display
    @param foods - array of foodTag structs where food data is stored, used to retrieve calorie information for calculating total calories of the recommended recipe
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through for calorie information
    Pre-condition: there must be at least 1 main course recipe available that meets the calorie requirements, and the user must input valid choices when prompted to view the recommended recipe.
*/
void displayMainCourse (int mainRecipes[], int starterCount, int mainIndex, struct recipeTag recipes[], struct foodTag foods[], int foodCount)
{
    printf("\n");
    longDivider();
    printf("|>                          RECOMMENDED MAIN COURSE                           <|\n");
    displayRecipe(recipes[mainIndex], foods, foodCount);
    printf("\n");
}

/*
This function displays the recommended starter course recipe based on the user's target calorie intake
    @param starterRecipes - array of indices for recipes classified as "starter" in the recipes array
    @param starterCount - the number of starter recipes available, used to determine if there are valid starter options to consider for calorie calculations
    @param starterIndex - the index of the recommended starter course recipe in the recipes array, used to retrieve and display the recipe details
    @param recipes - array of recipeTag structs where recipe data is stored, used to retrieve recipe details for display
    @param foods - array of foodTag structs where food data is stored, used to retrieve calorie information for calculating total calories of the recommended recipe
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through for calorie information
    Pre-condition: there must be at least 1 starter course recipe available that meets the calorie requirements, and the user must input valid choices when prompted to view the recommended recipe.
*/
void displayStarterCourse (int starterRecipes[], int starterCount, int starterIndex, struct recipeTag recipes[], struct foodTag foods[], int foodCount)
{
    printf("\n");
    longDivider();
    printf("|>                           RECOMMENDED STARTER                              <|\n");
    displayRecipe(recipes[starterIndex], foods, foodCount);
    printf("\n");
}

/*
This function displays the recommended dessert course recipe based on the user's target calorie intake
    @param dessertRecipes - array of indices for recipes classified as "dessert" in the recipes array
    @param dessertCount - the number of dessert recipes available, used to determine if there are valid dessert options to consider for calorie calculations
    @param dessertIndex - the index of the recommended dessert course recipe in the recipes array, used to retrieve and display the recipe details
    @param recipes - array of recipeTag structs where recipe data is stored, used to retrieve recipe details for display
    @param foods - array of foodTag structs where food data is stored, used to retrieve calorie information for calculating total calories of the recommended recipe
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through for calorie information
    Pre-condition: there must be at least 1 dessert course recipe available that meets the calorie requirements, and the user must input valid choices when prompted to view the recommended recipe.
*/
void displayDessertCourse (int dessertRecipes[], int dessertCount, int dessertIndex, struct recipeTag recipes[], struct foodTag foods[], int foodCount)
{
    printf("\n");
    longDivider();
    printf("|>                           RECOMMENDED DESSERT                              <|\n");
    displayRecipe(recipes[dessertIndex], foods, foodCount);
    printf("\n");
}

/*
This function recommends a menu to the user based on their target calorie intake and the available recipes, allowing them to view the details of the recommended main course, starter, and dessert recipes that meet their calorie requirements.
    @param recipes - array of recipeTag structs where recipe data is stored, used to retrieve recipe details for display and calorie calculations
    @param recipeCount - the number of recipe entries currently stored, used to determine how many entries to search through for recommendations
    @param foods - array of foodTag structs where food data is stored, used to retrieve calorie information for calculating total calories of the recommended recipes
    @param foodCount - the number of food entries currently stored, used to determine how many entries to search through for calorie information
    Pre-condition: there must be at least 1 recipe entry available that meets the calorie requirements for each course (main, starter, dessert)
    in order for recommendations to be made, and the user must input valid choices when prompted to view the recommended recipes.
*/
void recommendMenu (struct recipeTag recipes[], int recipeCount, struct foodTag foods[], int foodCount)
{
    float targetCalories, remainingCalories;
    int i, tries, picked, foundValid;
    char nextChoice;

    int mainCount = 0, starterCount = 0, dessertCount = 0;
    int mainRecipes[MAX_RECIPES];
    int starterRecipes[MAX_RECIPES];
    int dessertRecipes[MAX_RECIPES];
    int mainIndex=-1, starterIndex=-1, dessertIndex=-1;
    float mainCalories, starterCalories, dessertCalories;

    printf("\n");
    longDivider();
    printf("|>        ----------        RECOMMEND MENU FUNCTION        ----------         <|\n");
    longDivider();

    if (recipeCount == 0)
    {
        printf("|>         ----------       NO RECIPES AVAILABLE!        ----------           <|\n");
        longDivider();
        printf("\n");
    }

    else
    {
        printf("| --> Enter target calorie intake for 1 person: ");
        scanf("%f", &targetCalories);
        remainingCalories = targetCalories;
        printf("|%78s|\n", " ");
        longDivider();
        printf("\n");

        for (i = 0; i < recipeCount; i++)
        {
            if (caseInsensitiveCompare(recipes[i].classification, "main") == 0)
            {
                mainRecipes[mainCount] = i;
                mainCount++;
            }
            else if (caseInsensitiveCompare(recipes[i].classification, "starter") == 0)
            {
                starterRecipes[starterCount] = i;
                starterCount++;
            }
            else if (caseInsensitiveCompare(recipes[i].classification, "dessert") == 0)
            {
                dessertRecipes[dessertCount] = i;
                dessertCount++;
            }
        }

        srand(time(NULL));
        // random picks
        if (mainCount > 0)
        {
            foundValid = 0;
            for (tries = 0; tries < mainCount && foundValid == 0; tries++)
            {
                picked = mainRecipes[rand() % mainCount];
                mainCalories = calculateRecipeCalories(recipes[picked], foods, foodCount);

                if (mainCalories <= remainingCalories)
                {
                    mainIndex = picked;
                    foundValid = 1;
                }
            }

            if (mainIndex != -1)
            {
                longDivider();
                printf("| --> A valid main course is available. Show it? [Y/N]: ");
                scanf(" %c", &nextChoice);

                while (nextChoice != 'Y' && nextChoice != 'y' && nextChoice != 'N' && nextChoice != 'n')
                {
                    printf("| --> Invalid choice. Enter Y or N: ");
                    scanf(" %c", &nextChoice);
                }

                if (nextChoice == 'Y' || nextChoice == 'y')
                {
                    displayMainCourse(mainRecipes, mainCount, mainIndex, recipes, foods, foodCount);
                    remainingCalories = remainingCalories - mainCalories;
                }
            }
        }

        // only ask/show if a valid starter exists under remaining calories
        if (starterCount > 0)
        {
            foundValid = 0;
            for (tries = 0; tries < starterCount && foundValid == 0; tries++)
            {
                picked = starterRecipes[rand() % starterCount];
                starterCalories = calculateRecipeCalories(recipes[picked], foods, foodCount);

                if (starterCalories <= remainingCalories)
                {
                    starterIndex = picked;
                    foundValid = 1;
                }
            }

            if (starterIndex != -1)
            {
                longDivider();
                printf("| --> A valid starter is available. Show it? [Y/N]: ");
                scanf(" %c", &nextChoice);

                while (nextChoice != 'Y' && nextChoice != 'y' && nextChoice != 'N' && nextChoice != 'n')
                {
                    printf("| --> Invalid choice. Enter Y or N: ");
                    scanf(" %c", &nextChoice);
                }

                if (nextChoice == 'Y' || nextChoice == 'y')
                {
                    displayStarterCourse(starterRecipes, starterCount, starterIndex, recipes, foods, foodCount);
                    remainingCalories = remainingCalories - starterCalories;
                }
            }
        }

        if (dessertCount > 0)
        {
            foundValid = 0;
            for (tries = 0; tries < dessertCount && foundValid == 0; tries++)
            {
                picked = dessertRecipes[rand() % dessertCount];
                dessertCalories = calculateRecipeCalories(recipes[picked], foods, foodCount);

                if (dessertCalories <= remainingCalories)
                {
                    dessertIndex = picked;
                    foundValid = 1;
                }
            }

            if (dessertIndex != -1)
            {
                longDivider();
                printf("| --> A valid dessert is available. Show it? [Y/N]: ");
                scanf(" %c", &nextChoice);

                while (nextChoice != 'Y' && nextChoice != 'y' && nextChoice != 'N' && nextChoice != 'n')
                {
                    printf("| --> Invalid choice. Enter Y or N: ");
                    scanf(" %c", &nextChoice);
                }

                if (nextChoice == 'Y' || nextChoice == 'y')
                {
                    displayDessertCourse(dessertRecipes, dessertCount, dessertIndex, recipes, foods, foodCount);
                    remainingCalories = remainingCalories - dessertCalories;
                }
            }
        }

        if (mainIndex == -1 && starterIndex == -1 && dessertIndex == -1)
        {
            longDivider();
            printf("|>        ----------   NO VALID MENU FOR TARGET CALORIES   ----------        <|\n");
            longDivider();
        }
    }
}

int getChoiceUpdate (int nChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount, shortString passKey) 
{
    int res = 1;

    switch(nChoice)
    {
        case 1:
            addFoodCalories(foods, foodCount);
            returnToUpdate();
            res = -1;
            break;
        case 2:
            viewFoodCalories(foods, *foodCount);
            returnToUpdate();
            res = -1;
            break;
        case 3:
            saveCalories(foods, *foodCount);
            returnToUpdate();
            res = -1;
            break;
        case 4:
            loadCalories(foods, foodCount);
            returnToUpdate();
            res = -1;
            break;
        case 5:
            addRecipe(recipes, recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 6:
            modifyRecipe(recipes, *recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 7:
            deleteRecipe(recipes, recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 8:
            listRecipe(recipes, *recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 9:
            scanRecipe(recipes, *recipeCount, foods, *foodCount);
            returnToUpdate();
            res = -1;
            break;
        case 10:
            searchRecipe(recipes, *recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 11:
            exportRecipe(recipes, *recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 12:
            importRecipe(recipes, recipeCount);
            returnToUpdate();
            res = -1;
            break;
        case 13:
            changePassword(passKey);
            returnToUpdate();
            res = -1;
            break;
        case 14:
            *foodCount = 0;
            *recipeCount = 0;
            returnToMain();
            res = 0;
            break;
        
        default: 
        {
            printf("|>                         Invalid Option! Try again.                         <|\n");
            longDivider();
            printf("\n");
            res=-1;
        }
    }
    
    return res;
}

int getChoiceAccess (int nChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount) 
{
    int res = 1;

    switch(nChoice)
    {
        case 1:
            importRecipe(recipes, recipeCount);
            returnToAccess();
            res = -1;
            break;
        case 2:
            listRecipe(recipes, *recipeCount);
            returnToAccess();;
            res = -1;
            break;
        case 3:
            scanRecipe(recipes, *recipeCount, foods, *foodCount);
            returnToAccess();
            res = -1;
            break;
        case 4:
            searchRecipe(recipes, *recipeCount);
            returnToAccess();
            res = -1;
            break;
        case 5:
            generateShoppingList(recipes, *recipeCount);
            returnToAccess();
            res = -1;
            break;
        case 6:
            scanIngredient(recipes, *recipeCount, foods, *foodCount);
            returnToAccess();
            res = -1;
            break;
        case 7:
            recommendMenu(recipes, *recipeCount, foods, *foodCount);
            returnToAccess();
            res = -1;
            break;
        case 8:
            returnToMain();
            res = 0; 
            break;
        
        default: 
        {
            printf("|>                         Invalid Option! Try again.                         <|\n");
            longDivider();
            printf("\n");
            res=-1;
        }
    }
    
    return res;
}