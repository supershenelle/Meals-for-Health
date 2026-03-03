#include <stdio.h>
#include "functions.h"

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


int main ()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];

    mainMenu();
    updateMode();

    return 0;
}