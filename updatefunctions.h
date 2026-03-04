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
    /*
	Displays options for updateMenu
	*/
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
