// run code using: gcc main.c then call ./a.out in terminal

// FOR TESTING: USERNAME AND PASSWORD FOR LOGIN: 'a'

/*
UPDATE LOG: by shen
- 2026-03-12: Composed addRecipe() to add recipe with title, classification, servings, ingredients and steps

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
            : Created saveCalories() to save inputs
*/

#include <stdio.h>
#include "functions.h"

int main()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;

    displayMain(foods, &foodCount);

    return 0;
}
