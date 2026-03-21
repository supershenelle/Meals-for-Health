#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    float       calories;
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
    float                totalCalories;
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

int getChoiceUpdate (int nChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount);
void listRecipe (struct recipeTag recipes[], int recipeCount);

void getValidIntInput(int *choice)
{
    int valid = 0;
    int c;
    do
    {
        printf("|%3s --> Option: ", " ");
        if (scanf(" %d", choice) == 1)
            valid = 1;
        else
        {
            printf(">  Invalid Option! Try again.  <\n");
            // Clear input buffer
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } while (!valid);
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

int updateMode (struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount)
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

        do
        {
            updateMenu();
            printf("|%30s|\n", " ");
            getValidIntInput(&nChoice);
            printf("|%30s|\n", " ");
            displayDivider1();
            res = getChoiceUpdate(nChoice, foods, foodCount, recipes, recipeCount); 
        } while (res == -1); //ends loop if invalid input or input is exit update menu
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
        if (strcasecmp(foods[i].name, name) == 0)
            res = i; // return index of existing food
    }
    return res; // not found
}

int checkRecipeTitle (struct recipeTag recipes[], int recipeCount, shortString title)
{
    int res = -1;

    for (int i = 0; i < recipeCount; i++)
    {
        if (strcasecmp(recipes[i].title, title) == 0)
            res = i; // return index of existing recipe
    }
    return res; // not found
}

void sortRecipeTitle(struct recipeTag recipes[], int recipeCount)
{
    int x, y, min;
    struct recipeTag tempStruct; 

    for(x = 0; x < recipeCount - 1; x++)
    {
        min = x;
        for(y = x + 1; y < recipeCount; y++)
        {
            if(strcmp(recipes[y].title, recipes[min].title) < 0)
                min = y;
        }
        if(min != x)
        {
            // Swap the entire structs
            tempStruct = recipes[x];
            recipes[x] = recipes[min];
            recipes[min] = tempStruct;
        }
    }
}

int getChoice (char cChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount) 
{
    int res=1;
    
    switch(cChoice)
	{
		case 'U':
		case 'u':
            res = updateMode(foods, foodCount, recipes, recipeCount);
            if(res==0)
            {
                printf("\n");
                displayDivider1();
                printf("|     Exiting Update Menu...   |\n");
                displayDivider1();
                printf("\n");
                res=-1;
            }
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

void displayMain (struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount)
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
		
        res = getChoice(cChoice, foods, foodCount, recipes, recipeCount);
		
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
    FILE *sCal;
    int i;
    shortString filename;
    
    printf("\n >    SAVING FOOD CALORIES...  < \n");
    displayDivider2();
    printf("--> Enter filename to save (with .txt): ");
    printf("\n--> ");
    getString(filename);

    sCal = fopen(filename,"w");

    for(i=0;i<foodCount;i++)
    {
        fprintf(sCal, "%s\n", foods[i].name);
        fprintf(sCal, "%.2f %s %.2f\n\n", foods[i].quantity, foods[i].unit, foods[i].calories);
    }

    fclose(sCal);
}

void loadCalories(struct foodTag foods[], int *foodCount)
{
    /* 
    Load food entries from a text file and add them to the current list.
    If a food name already exists, prompt user to overwrite or keep existing data.
    */
   FILE *lCal;
   shortString filename;
   int existingIndex;
   char overwriteChoice;

    printf("\n>    LOADING FOOD CALORIES...  < \n");
    displayDivider2();
    printf("--> Enter filename to load (with .txt): ");
    printf("\n--> ");
    getString(filename);

    lCal = fopen(filename,"r");

    if(lCal == NULL)
    {
        printf("! File not found. Please check the filename and try again. !\n");
        displayDivider2();
    }
    else
    {
        while (*foodCount < 50 && !feof(lCal))
        {
            fscanf(lCal, " %20[^\n]", foods[*foodCount].name);
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
    }
        
    fclose(lCal);
}

void addRecipe (struct recipeTag recipes[], int *recipeCount)
{
    int count = 0;
    int stepCount = 0;
    int doneIngredients = 0;
    int doneSteps = 0;
    recipes[*recipeCount].totalCalories = 0;

    longDivider();
    printf("|>                            ADDING NEW RECIPE...                            <|\n");
    longDivider();

    printf("--> Enter recipe title: ");
    getString(recipes[*recipeCount].title);
    printf("--> Enter recipe classification: ");
    getString(recipes[*recipeCount].classification);
    if (strcmp(recipes[*recipeCount].classification, "starter") != 0 && strcmp(recipes[*recipeCount].classification, "main") != 0 && strcmp(recipes[*recipeCount].classification, "dessert") != 0)
    {
        do {
            printf("!    Invalid classification. Please enter 'starter', 'main', or 'dessert'.    !\n");
            printf("--> Enter recipe classification: ");
            getString(recipes[*recipeCount].classification);
        } while (strcmp(recipes[*recipeCount].classification, "starter") != 0 && strcmp(recipes[*recipeCount].classification, "main") != 0 && strcmp(recipes[*recipeCount].classification, "dessert") != 0);
    }
    printf("--> Enter number of servings: ");
    scanf(" %d", &recipes[*recipeCount].servings);
    printf("--> Enter ingredients (type 'done' when finished): \n");

    while (count < 20 && !doneIngredients)
    {
        printf("--> Ingredient %d name: ", count + 1);
        getString(recipes[*recipeCount].ingredients[count].item);

        if (strcmp(recipes[*recipeCount].ingredients[count].item, "done") == 0)
            doneIngredients = 1;

        else
        {
            printf("--> Ingredient %d quantity: ", count + 1);
            scanf(" %f", &recipes[*recipeCount].ingredients[count].quantity);
            printf("--> Ingredient %d unit: ", count + 1);
            getString(recipes[*recipeCount].ingredients[count].unit);
            printf("--> Ingredient %d calories per unit: ", count + 1);
            scanf(" %f", &recipes[*recipeCount].ingredients[count].calories);
            recipes[*recipeCount].totalCalories += 
                recipes[*recipeCount].ingredients[count].quantity 
                * recipes[*recipeCount].ingredients[count].calories;
            count++;
        }
    }
    recipes[*recipeCount].ingredientCount = count;

    printf("--> Enter steps (type 'done' when finished): \n");

    while (stepCount < 15 && !doneSteps) {
        printf("--> Step %d: ", stepCount + 1);
        getString(recipes[*recipeCount].steps[stepCount]);

        if (strcmp(recipes[*recipeCount].steps[stepCount], "done") == 0)
            doneSteps = 1;

        else
            stepCount++;
    }
    recipes[*recipeCount].stepCount = stepCount;
    (*recipeCount)++;
}

int checkIngredient (shortString ingredient, struct recipeTag recipes[], int nIndex)
{
    int res = -1;
    int i;

    for (i = 0; i < recipes[nIndex].ingredientCount; i++)
    {
        if (strcasecmp(recipes[nIndex].ingredients[i].item, ingredient) == 0)
            res = i;
    }
    return res; 
}

void deleteIngredient (shortString ingredient, struct recipeTag recipes[], int nIndex)
{
    int i;
    int ingredientIndex = checkIngredient(ingredient, recipes, nIndex);
    int lastIngredient = recipes[nIndex].ingredientCount; 

    if (ingredientIndex != -1)
    {
        for (i = ingredientIndex; i < lastIngredient; i++)
        { // shift ingredients  
            recipes[nIndex].ingredients[i] = recipes[nIndex].ingredients[i + 1];
        }
        
        // delete all info
        recipes[nIndex].ingredients[lastIngredient - 1].item[0] = '\0';
        recipes[nIndex].ingredients[lastIngredient - 1].quantity = 0.0f;
        recipes[nIndex].ingredients[lastIngredient - 1].unit[0] = '\0';
        recipes[nIndex].ingredientCount--;
    }
}

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

void modifyRecipe (struct recipeTag recipes[], int recipeCount)
{
    shortString tempTitle, tempIngredient;
    int cOpt = -1;
    int index;
    int delIdx;
    int ingredientCount, stepCount, nStep; //nstep index of step to be deleted

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
                    printf("--> Enter ingredient calories per unit: ");
                    scanf(" %f", &recipes[index].ingredients[ingredientCount].calories);
                    recipes[index].totalCalories += 
                        recipes[index].ingredients[ingredientCount].quantity * 
                        recipes[index].ingredients[ingredientCount].calories;
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

                    delIdx = checkIngredient(tempIngredient, recipes, index);
                    recipes[index].totalCalories -=
                        recipes[index].ingredients[delIdx].quantity *
                        recipes[index].ingredients[delIdx].calories;
                    
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

                else
                {
                    listSteps(recipes, index);
                    printf("|                               DELETING A STEP                                |\n");
                    printf("--> Enter the step number to delete: ");
                    scanf(" %d", &nStep);

                    if (nStep < 1 || nStep > stepCount)
                    {
                        do {
                            printf("|>        ----------          INVALID STEP NUMBER!         ----------        <|\n");
                            longDivider();
                            printf("--> Enter the step number to delete: ");
                            scanf(" %d", &nStep);
                        } while (nStep < 1 || nStep > stepCount);
                    }

                    deleteStep(nStep, recipes, index);
                    printf("|>     ----------       STEP DELETED SUCCESSFULLY!       ----------     <|\n");
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

void listRecipe (struct recipeTag recipes[], int recipeCount)
{
    int i;

    sortRecipeTitle(recipes, recipeCount); // sort recipes by title before listing

    printf("\n");
    if (recipeCount == 0)
    {
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
            printf("| %d. %33s | %18s | %16d |\n",
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

void scanRecipe (struct recipeTag recipes[], int recipeCount)
{
    int i=0;
    int j;
    char cOpt;
    
    sortRecipeTitle(recipes, recipeCount); // sort recipes by title before scanning

    printf("\n");
    if (recipeCount == 0)
    {
        printf("|>       ----------          NO FOOD RECIPES FOUND!          ----------       <|\n");
        longDivider();
    }
    else
    {
        do{
        longDivider();
        printf("|>                          SCANNING FOOD RECIPE %2d                           <|\n", i + 1);
        printf("|             Recipe Title             |   Servings   |     Total Calories     |\n");
        printf("|==============================================================================|\n");
        printf("| %37s | %12d | %20.2f |\n",recipes[i].title, recipes[i].servings, recipes[i].totalCalories);
        printf("|                                  Ingredients                                 |\n");
        printf("|    Quantity    |   Unit   |          Food Name          |       Calories     |\n");
        printf("|>        ----------       SCAN FOOD RECIPES SUCCESS!       ----------        <|\n");
        for(j = 0; j < recipes[i].ingredientCount; j++)
        {
            printf("| %13.2f | %8s | %23s | %18.2f |\n",
                recipes[i].ingredients[j].quantity,
                recipes[i].ingredients[j].unit,
                recipes[i].ingredients[j].item,
                recipes[i].ingredients[j].calories);
        }

        printf("|                                   Procedure                                  |\n");
        
        for(j = 0; j < recipes[i].stepCount; j++)
        {
            printf("| %2d: %71s |\n", j + 1, recipes[i].steps[j]);
        }

        printf("|>        ----------       SCAN FOOD RECIPES SUCCESS!       ----------        <|\n");
        printf("\n");
        printf("|>                               CHOOSE OPTION.                               <|\n");
        printf("|>                  [P] Go to Previous Recipe                                 <|\n");
        printf("|>                  [N] Go to Next Recipe                                     <|\n");
        printf("|>                  [X] Return to Update Recipe Box Menu                      <|\n");
        printf("| Option: ");
        scanf(" %c", &cOpt);
        
        switch(cOpt)
        {
            case 'P':
            case 'p':
                if(i == 0)
                {
                    printf("|>      ----------         THIS IS THE FIRST RECIPE!        ----------        <|\n");
                    longDivider();
                }
                else
                    i--;
                break;

            case 'N':
            case 'n':
                if(i == recipeCount - 1)
                {
                    printf("|>      ----------         THIS IS THE LAST RECIPE!         ----------        <|\n");
                    longDivider();
                }
                else
                    i++;
                break;

             default:
                printf("|>                Invalid option! Please enter a valid option.                <|\n");
                longDivider();
                break;
        }
        }while(cOpt != 'X' && cOpt != 'x');

    }
}

void searchRecipe (struct recipeTag recipes[], int recipeCount)
{
    
}

void exportRecipe (struct recipeTag recipes[], int recipeCount)
{
    FILE *eRec;
    int i, j;
    shortString filename;
    
    printf("\n>       EXPORTING RECIPES...   < \n");
    displayDivider2();
    printf("--> Enter filename to export (with .txt): ");
    printf("\n--> ");
    getString(filename);

    eRec = fopen(filename,"w");

    for(i=0;i<recipeCount;i++)
    {
        fprintf(eRec, "%s\n", recipes[i].title);
        fprintf(eRec, "%d %s\n", recipes[i].servings, recipes[i].classification);
        fprintf(eRec, "Ingredients %d\n", recipes[i].ingredientCount);
        for (int j = 0; j < recipes[i].ingredientCount; j++)
        {
            fprintf(eRec, "%f %s %s\n", recipes[i].ingredients[j].quantity, 
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

void importRecipe (struct recipeTag recipes[], int *recipeCount)
{
   FILE *iRec;
   shortString filename;
   int existingIndex;
   char overwriteChoice;

    printf("\n>       IMPORTING RECIPES...   < \n");
    displayDivider2();
    printf("--> Enter filename to import (with .txt): ");
    printf("\n--> ");
    getString(filename);

    iRec = fopen(filename,"r");

    if(iRec == NULL)
    {
        printf("! File not found. Please check the filename and try again. !\n");
        displayDivider2();
    }
    else
    {
        while (*recipeCount < 50 && !feof(iRec))
        {
            fscanf(iRec, " %20[^\n]", recipes[*recipeCount].title);
            fscanf(iRec, "%*c"); 

            // Read servings and classification directly to struct fields
            fscanf(iRec, " %d %20s", &recipes[*recipeCount].servings, recipes[*recipeCount].classification);
            fscanf(iRec, "%*c"); 



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
    }
        
    fclose(lCal);
}

int getChoiceUpdate (int nChoice, struct foodTag foods[], int *foodCount, struct recipeTag recipes[], int *recipeCount) 
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
            res = -1;
            break;
        case 2:
            viewFoodCalories(foods, *foodCount);
            printf("\n");
            res = -1;
            break;
        case 3:
            saveCalories(foods, *foodCount); 
            printf("==   FILE SAVED SUCCESSFULLY  ==\n");
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 4:
            loadCalories(foods, foodCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 5:
            addRecipe(recipes, recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 6:
            modifyRecipe(recipes, *recipeCount);
            printf("\n");
            res = -1;
            break;
        case 7:
            deleteRecipe(recipes, recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 8:
            listRecipe(recipes, *recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 9:
            scanRecipe(recipes, *recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 10:
            searchRecipe(recipes, *recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 11:
            exportRecipe(recipes, *recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 12:
            importRecipe(recipes, recipeCount);
            printf("== Returning to Update Menu.. ==\n");
            displayDivider2();
            printf("\n");
            res = -1;
            break;
        case 13:
            //displayMain(foods, foodCount);
            res = 0;
            break;
        
        default: 
        {
            printf("Invalid Option! Please try again\n\n");
            res=-1;
        }
    }
    
    return res;
}