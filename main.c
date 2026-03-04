// run code using: gcc main.c then call ./a.out in terminal

/*
UPDATE LOG: by shen
- 2026-03-03: Composed structures for food and recipe data
            : Added mainMenu() function to display the main menu
            : Implemented updateMode() function for user authentication
            : Created getString() function to safely read strings from user input
            : Developed foodCalories() function to add food entries with validation to prevent duplicates
            : Added checkFoodName() function to check for existing food names in the array
            : Updated main() function to test the foodCalories() function and display entered food data

UPDATE LOG: by marco
- 2026-03-04: Composed getChoice() to get input from use what mode to do
			: Composed displayMain() to display mainMenu and choices
			: Fixed order of updateMode() to fit in with displayMain()
			: Created updatefunctions header
			: Created getChoiceUpdate() to pick options for updateMenu
			: Created displayUpdate() to display updateMenu and choices
*/

#include <stdio.h>
#include "functions.h"
#include "updatefunctions.h"

int main ()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;

    displayMain();
    
    foodCalories(foods, &foodCount);
    foodCalories(foods, &foodCount); // call again to test next index for food entry

    int t = 0; //for TESTING of display. change to diff index for diff food entry
    printf("\nEnter food index to display: ");
    scanf(" %d", &t);
    printf("\nTEST\n");
    printf("Food name: %s\n", foods[t].name);
    printf("Quantity: %.2f\n", foods[t].quantity);
    printf("Unit: %s\n", foods[t].unit);
    printf("Calories: %.2f\n", foods[t].calories);

    return 0;
}
