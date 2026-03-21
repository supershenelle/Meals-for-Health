#include <stdio.h>
#include "functions.h"

// =====================================================================================================
// TEST FUNCTION FOR MODIFY RECIPE

static void initRecipe(struct recipeTag *recipe,
                       const char *title,
                       const char *classification,
                       int servings)
{
    int i;

    strcpy(recipe->title, title);
    strcpy(recipe->classification, classification);
    recipe->servings = servings;

    for (i = 0; i < 20; i++)
    {
        recipe->ingredients[i].item[0] = '\0';
        recipe->ingredients[i].quantity = 0.0f;
        recipe->ingredients[i].unit[0] = '\0';
    }

    for (i = 0; i < 15; i++)
        recipe->steps[i][0] = '\0';
}

static void seedTestRecipes(struct recipeTag recipes[], int *recipeCount)
{
    *recipeCount = 2;

    initRecipe(&recipes[0], "pasta", "main", 2);
    strcpy(recipes[0].ingredients[0].item, "pasta");
    recipes[0].ingredients[0].quantity = 200.0f;
    strcpy(recipes[0].ingredients[0].unit, "grams");
    strcpy(recipes[0].ingredients[1].item, "salt");
    recipes[0].ingredients[1].quantity = 5.0f;
    strcpy(recipes[0].ingredients[1].unit, "grams");
    strcpy(recipes[0].ingredients[2].item, "done");

    strcpy(recipes[0].steps[0], "boil water");
    strcpy(recipes[0].steps[1], "cook pasta");
    strcpy(recipes[0].steps[2], "done");

    initRecipe(&recipes[1], "fruitcup", "dessert", 1);
    strcpy(recipes[1].ingredients[0].item, "apple");
    recipes[1].ingredients[0].quantity = 1.0f;
    strcpy(recipes[1].ingredients[0].unit, "piece");
    strcpy(recipes[1].ingredients[1].item, "done");

    strcpy(recipes[1].steps[0], "slice fruit");
    strcpy(recipes[1].steps[1], "serve");
    strcpy(recipes[1].steps[2], "done");
}

int main(void)
{
    struct recipeTag recipes[50];
    int recipeCount = 0;
    char again = 'Y';

    seedTestRecipes(recipes, &recipeCount);
    printf("\nLoaded %d sample recipes for modifyRecipe() testing.\n", recipeCount);

    while (again == 'Y' || again == 'y')
    {
        modifyRecipe(recipes, recipeCount);
        listRecipe(recipes, recipeCount);

        printf("\nTest modify recipe again? (Y/N): ");
        scanf(" %c", &again);
    }

    return 0;
}
