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

