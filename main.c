// run code using: gcc main.c then call ./a.out in terminal

/*
UPDATE LOG: by shen
- 2026-03-03: Composed updateMenu() to display update menu and choices

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
// #include "updatefunctions.h"

int main ()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;

    displayMain(foods, foodCount);

    return 0;
}
