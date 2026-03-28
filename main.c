// run code using: gcc main.c then call ./a.out in terminal

// FOR TESTING: USERNAME AND PASSWORD FOR LOGIN: 'a'

/*
FINAL REVISIONS FOR EVERYONE:
1. separate helper functions
2. add comments to functions
4. change password (bonus)
5. add clear bg header
6. test cases

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
