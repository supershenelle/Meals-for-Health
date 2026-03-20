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
- 2026-03-14: Finished implementing loadCalories() function to load food calorie data from a text file
            : Fixed getChoiceUpdate() to return -1 after each case to loop back to update menu until user chooses to exit
            : Created getValidIntInput() function to validate integer input for update menu choices
            : Fixed checkfoodName() to be case-insensitive when checking for existing food names
            : Fixed getChoice() to return -1 after each case to loop back to main menu until user chooses to exit
            : Fixed updateMode() to have a do while loop that continues to show update menu until user chooses to exit
            : Added ctype library to functions.h for case-insensitive string comparison in checkFoodName()
            : Created listRecipes() function to display all recipes with their details
            : Created checkRecipeTitle() function to check if a recipe with a given title exists
            : Updated all functions to include recipe parameters where necessary
            : Created deleteRecipe() function to delete a recipe by title
*/

#include <stdio.h>
#include "functions.h"

int main()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;
    int recipeCount = 0;

    displayMain(foods, &foodCount, recipes, &recipeCount);

    return 0;
}
