#include <stdio.h>
#include <string.h>
// #include "updatefunctions.h"

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

void displayDivider1()
{
    printf("================================\n");
}

void displayDivider2()
{
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
}

void longDivider()
{
    printf("|==============================================================================|\n");
}

int getChoiceUpdate (int nChoice, struct foodTag foods[], int *foodCount);

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
    displayDivider1();
    printf("| %28s |\n", " ");
    printf("| %2s UPDATE MENU %13s |\n", " ", " ");
    printf("| %2s [1] Add Food Calories %4s|\n", " ", " ");
    printf("| %2s [2] View Food Calories %3s|\n", " ", " ");
    printf("| %2s [3] Save Calories %8s|\n", " ", " ");
    printf("| %2s [4] Load Calories %8s|\n", " ", " ");
    printf("| %2s [5] Add Recipe %11s|\n", " ", " ");
    printf("| %2s [6] Modify Recipe %8s|\n", " ", " ");
    printf("| %2s [7] Delete Recipe %8s|\n", " ", " ");
    printf("| %2s [8] List Recipes %9s|\n", " ", " ");
    printf("| %2s [9] Scan Recipe %10s|\n", " ", " ");
    printf("| %2s [10] Search Recipe %7s|\n", " ", " ");
    printf("| %2s [11] Export Recipe %7s|\n", " ", " ");
    printf("| %2s [12] Import Recipe %7s|\n", " ", " ");
    printf("| %2s [13] Exit Update Menu %4s|\n", " ", " ");
}

int updateMode (struct foodTag foods[], int *foodCount)
{
    int res;
    int nChoice;
    shortString user;
    shortString pass;
    shortString userKey = "a";
    shortString passKey = "a";

    printf("-->%1s Enter username: ", " ");
    scanf(" %s", user);
    printf("-->%1s Enter password: ", " ");
    scanf(" %s", pass);
    
    if (strcmp(user, userKey)==0 && strcmp(pass, passKey)==0)
    {
        printf(">   USER VALIDATED / SUCCESS   <\n");
        displayDivider2();
        printf("\n");

        updateMenu();
        printf("|%30s|\n", " ");
        printf("|%3s --> Option: ", " ");
        scanf(" %d", &nChoice);
        printf("|%30s|\n", " ");
        displayDivider1();
        res = getChoiceUpdate(nChoice, foods, foodCount); 
    }
        
    else
    {
        printf("> INVALID USERNAME OR PASSWORD <\n");
        displayDivider2();
        printf("\n");
        res = -1;
    }
    
    return res;
}

void mainMenu ()
{
    displayDivider1();
    printf("| %28s |\n", " ");
    printf("| %4s MAIN MENU %13s |\n", " ", " ");
    printf("| %4s [U] Update Menu %8s|\n", " ", " ");
    printf("| %4s [A] Access Menu %8s|\n", " ", " ");
    printf("| %4s [E] Exit Menu %10s|\n", " ", " ");
    printf("| %28s |\n", " ");
    displayDivider1();
    printf("\n");
}

int checkFoodName (struct foodTag foods[], int foodCount, shortString name)
{
    int res = -1;

    for (int i = 0; i < foodCount; i++)
    {
        if (strcmp(foods[i].name, name) == 0)
            res = i; // return index of existing food
    }
    return res; // not found
}

int getChoice (char cChoice, struct foodTag foods[], int *foodCount) 
{
    int res=1;
    
    switch(cChoice)
	{
		case 'U':
		case 'u':
			res = updateMode(foods, foodCount);
			break;
		case 'A':
		case 'a':
			/*accessMenu function*/;
			break;
		case 'E':
		case 'e':
			{
			/*exitMenu function*/;
			res=0;
			} 
			break;
		
		default: 
		{
			printf(">  Invalid Option! Try again.  <\n");
            displayDivider2();
            printf("\n");
			res=-1;
		}
	}
	
	return res;
}

void displayMain (struct foodTag foods[], int *foodCount)
{
    char cChoice;
    int res;
    do
	{
		mainMenu();
        displayDivider2();
		printf("-->%1s Enter Mode: ", "");
        scanf(" %c",&cChoice);
        displayDivider2();
		
		res = getChoice(cChoice, foods, foodCount);
		
	}while(res==-1); //ends loop if invalid input or input is exit
	
}

void addFoodCalories (struct foodTag foods[], int *foodCount)
{
    int i = *foodCount; // get current count of food entries
    shortString temp; // temporary string for food name input and checking
    int scanResult;

    printf("\n >    ADDING FOOD CALORIES...  < \n");
    displayDivider2();

    do {
        printf("--> Enter food name: ");
        getString(temp);

        if (checkFoodName(foods, *foodCount, temp) != -1)
            printf("! Food exists // View Number %d !\n> -- Enter a different name -- <\n", (checkFoodName(foods, *foodCount, temp)) + 1);
        else
            strcpy(foods[i].name, temp);
    } while (checkFoodName(foods, *foodCount, temp) != -1);
    
    do {
        printf("--> Enter quantity: ");
        scanResult = scanf(" %f", &foods[i].quantity);

        if (scanResult != 1)
        {
            foods[i].quantity = 0; //fix when character is inputted, quantity becomes 0 and loop continues to run but with invalid input
            printf("--> Invalid input. Please enter a number.\n > -- Please try again. -- <\n");
        }
        else if (foods[i].quantity <= 0)
        {
            printf("!  QTY can't be 0 or negative  !\n>  --   Please try again   --  <\n");
        }

    } while (scanResult != 1 || foods[i].quantity <= 0);

    printf("--> Enter unit: ");
    getString(foods[i].unit);
    printf("--> Enter calories: ");
    scanf(" %f", &foods[i].calories);
    (*foodCount)++; // increment food count for next entry
}

char nextFoodEntry(int foodCount)
{
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
        printf("|>     ----------         NO FOOD CALORIE ENTRY!        ----------      <|\n");
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
    /*
    Save the food entries to a file for later retrieval.
    */
}

int getChoiceUpdate (int nChoice, struct foodTag foods[], int *foodCount) 
{
    int res = 1;

    switch(nChoice)
    {
        case 1:
            addFoodCalories(foods, foodCount);
            printf("==  FOOD ADDED SUCCESSFULLY!  ==\n");
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            updateMenu();
            printf("|%30s|\n", " ");
            printf("|%3s --> Option: ", " ");
            scanf(" %d", &nChoice);
            printf("|%30s|\n", " ");
            displayDivider1();
            res = getChoiceUpdate(nChoice, foods, foodCount);
            break;
        case 2:
            viewFoodCalories(foods, *foodCount);
            printf("\n");
            updateMenu();
            printf("|%30s|\n", " ");
            printf("|%3s --> Option: ", " ");
            scanf(" %d", &nChoice);
            printf("|%30s|\n", " ");
            displayDivider1();
            res = getChoiceUpdate(nChoice, foods, foodCount);
            break;
        case 3:
            saveCalories(foods, *foodCount); 
            break;
        case 4:
            //res = loadCalories();
            break;
        case 5:
            //res = addReceipe();
            break;
        case 6:
            //res = modReceipe();
            break;
        case 7:
            //res = deleteReceipe();
            break;
        case 8:
            //res = listReceipe();
            break;
        case 9:
            //res = scanReceipe();
            break;
        case 10:
            //res = searchReceipe();
            break;
        case 11:
            //res = exportReceipe();
            break;
        case 12:
            //res = importReceipe();
            break;
        case 13:
            displayMain(foods, foodCount);
            break;
        
        default: 
        {
            printf("Invalid Option! Please try again\n\n");
            res=-1;
        }
    }
    
    return res;
}