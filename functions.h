#include <stdio.h>
#include <string.h>
#include "updatefunctions.h"

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

int updateMode ()
{
    int res;
    int nChoice;
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
        updateMenu();
        printf("| Option: ");
        scanf(" %d", &nChoice);
        printf("%25s |", " ");
        res = getChoiceUpdate(nChoice);
    }
        
    else
    {
        printf("Invalid username or password\n");
        res = -1;
    }
    
    return res;
}

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

int getChoice (char cChoice) 
{
    int res=1;
    
    switch(cChoice)
	{
		case 'U':
		case 'u':
			res = updateMode()/*updateMenu function*/;
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
			printf("Invalid Option! Please try again\n\n");
			res=-1;
		}
	}
	
	return res;
}

void displayMain ()
{
    char cChoice;
    int res;
    do
	{
		mainMenu();
		printf("Mode:");
		scanf(" %c",&cChoice);
		
		res = getChoice(cChoice);
		
	}while(res==-1); //ends loop if invalid input or input is exit
	
}

void addFoodCalories (struct foodTag foods[], int *foodCount)
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
    int i;
    
    for(i=0;i<foodCount;i++)
	{
		printf("Food Item #%d: %s\n", i+1, foods[i].name);
		printf("\t Quantity: %f \n",foods[i].quantity);
		printf("\t Unit: %s \n",foods[i].unit);
		printf("\t Calories: %f \n",foods[i].calories);
	}
    
}

void saveCalories (struct foodTag foods[], int foodCount)
{
    /*
    Save the food entries to a file for later retrieval.
    */
}

void updateMenu ()
{
    printf("============================\n");
    printf("| %24s |\n", " ");
    printf("| %4s UPDATE MENU %7s |\n", " ", " ");
    printf("| %4s [1] Add Food Calories %2s|\n", " ", " ");
    printf("| %4s [2] View Food Calories %1s|\n", " ", " ");
    printf("| %4s [3] Save Calories %8s|\n", " ", " ");
    printf("| %4s [4] Load Calories %8s|\n", " ", " ");
    printf("| %4s [5] Add Recipe %11s|\n", " ", " ");
    printf("| %4s [6] Modify Recipe %6s|\n", " ", " ");
    printf("| %4s [7] Delete Recipe %6s|\n", " ", " ");
    printf("| %4s [8] List Recipes %9s|\n", " ", " ");
    printf("| %4s [9] Scan Recipe %9s|\n", " ", " ");
    printf("| %4s [10] Search Recipe%5s|\n", " ", " ");
    printf("| %4s [11] Export Recipe%5s|\n", " ", " ");
    printf("| %4s [12] Import Recipe%5s|\n", " ", " ");
    printf("| %4s [13] Exit Update Menu%1s|\n", " ", " ");
}
int getChoiceUpdate (int nChoice) 
{
    int res=1;
    
    switch(nChoice)
	{
		case '1':
			res = addFoodCalories(foods,*foodCount);
			break;
		case '2':
			res = viewFoodCalories(foods,foodCount);
			break;
		case '3':
			res = saveCalories(foods,foodCount);
			break;
		case '4':
			//res = loadCalories();
			break;
		case '5':
			//res = addReceipe();
			break;
		case '6':
			//res = modReceipe();
			break;
		case '7':
			//res = deleteReceipe();
			break;
		case '8':
			//res = listReceipe();
			break;
		case '9':
			//res = scanReceipe();
			break;
		case '10':
			//res = searchReceipe();
			break;
		case '11':
			//res = exportReceipe();
			break;
		case '12':
			//res = importReceipe();
			break;
		case '13':
			{
			/*exitMenu function*/;
			res=0;
			} 
			break;
		
		default: 
		{
			printf("Invalid Option! Please try again\n\n");
			res=-1;
		}
	}
	
	return res;
}

void displayUpdate()
{
    int nChoice;
    int res;
    do
	{
		updateMenu();
		printf("Mode:");
		scanf(" %d",&nChoice);
		
		res = getChoiceUpdate(nChoice);
		
	}while(res==-1); //ends loop if invalid input or input is exit
	
}