// run code using: gcc main.c then call ./a.out in terminal

/*
UPDATE LOG: by shen
- 2026-03-07: Applied validation for food name input in addFoodCalories() to prevent duplicate entries
            : Applied validation for quantity input in addFoodCalories() to prevent invalid input and negative numbers
            : Fixed UI and display
            : Made option 1 and 2 from updateMenu functional
            : Finished viewFoodCalories() to display food entries in pages of 10 with option to view next page or exit view
            : Added testfunctions.c to generate test food entries and test viewFoodCalories() function
            : viewFoodCalories() now displays message if there are no food entries to show
            : viewFoodCalories() allows two input choices: 'N' to view next page of entries or 'X' to exit view, with validation for invalid input
            : viewFoodCalories() displays success message after viewing each page of entries

- NOTES/ISSUES
! Food name input is case-sensitive, so "Apple" and "apple" would be considered different entries. 
! Character input in quantity field causes quantity to become 0 and loop to continue running with invalid input.
____________________________________________________________________________________________________________________________________________________

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

int main()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;

    displayMain(foods, &foodCount);
    printf("ms nats protein maxxer");

    return 0;
}
