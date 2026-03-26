#include <stdio.h>
#include "functions.h"

// =====================================================================================================
// TEST FUNCTION FOR RECOMMEND MENU

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

static void seedFoods(struct foodTag foods[], int *foodCount)
{
    *foodCount = 7;

    strcpy(foods[0].name, "pasta");
    foods[0].quantity = 1.0f;
    strcpy(foods[0].unit, "gram");
    foods[0].calories = 1.31f;

    strcpy(foods[1].name, "apple");
    foods[1].quantity = 1.0f;
    strcpy(foods[1].unit, "piece");
    foods[1].calories = 95.0f;

    strcpy(foods[2].name, "tomato");
    foods[2].quantity = 1.0f;
    strcpy(foods[2].unit, "piece");
    foods[2].calories = 22.0f;

    strcpy(foods[3].name, "chicken");
    foods[3].quantity = 1.0f;
    strcpy(foods[3].unit, "gram");
    foods[3].calories = 1.65f;

    strcpy(foods[4].name, "rice");
    foods[4].quantity = 1.0f;
    strcpy(foods[4].unit, "gram");
    foods[4].calories = 1.3f;

    // Zero-calorie foods for edge-case testing.
    strcpy(foods[5].name, "water");
    foods[5].quantity = 1.0f;
    strcpy(foods[5].unit, "ml");
    foods[5].calories = 0.0f;

    strcpy(foods[6].name, "cucumber");
    foods[6].quantity = 1.0f;
    strcpy(foods[6].unit, "gram");
    foods[6].calories = 0.0f;
}

static void seedTestRecipes(struct recipeTag recipes[], int *recipeCount)
{
    *recipeCount = 6;

    // Recipe 1: pasta with tomato (matched + matched)
    initRecipe(&recipes[0], "pasta-tomato", "main", 2);
    strcpy(recipes[0].ingredients[0].item, "pasta");
    recipes[0].ingredients[0].quantity = 100.0f;
    strcpy(recipes[0].ingredients[0].unit, "grams");
    strcpy(recipes[0].ingredients[1].item, "tomato");
    recipes[0].ingredients[1].quantity = 200.0f;
    strcpy(recipes[0].ingredients[1].unit, "grams");
    strcpy(recipes[0].ingredients[2].item, "salt");
    recipes[0].ingredients[2].quantity = 5.0f;
    strcpy(recipes[0].ingredients[2].unit, "grams");
    strcpy(recipes[0].ingredients[3].item, "done");

    strcpy(recipes[0].steps[0], "boil water");
    strcpy(recipes[0].steps[1], "cook pasta");
    strcpy(recipes[0].steps[2], "add tomato");
    strcpy(recipes[0].steps[3], "done");

    // Recipe 2: chicken rice (matched + matched)
    initRecipe(&recipes[1], "chicken-rice", "main", 1);
    strcpy(recipes[1].ingredients[0].item, "chicken");
    recipes[1].ingredients[0].quantity = 150.0f;
    strcpy(recipes[1].ingredients[0].unit, "grams");
    strcpy(recipes[1].ingredients[1].item, "rice");
    recipes[1].ingredients[1].quantity = 70.0f;
    strcpy(recipes[1].ingredients[1].unit, "grams");
    strcpy(recipes[1].ingredients[2].item, "done");

    strcpy(recipes[1].steps[0], "cook rice");
    strcpy(recipes[1].steps[1], "fry chicken");
    strcpy(recipes[1].steps[2], "combine");
    strcpy(recipes[1].steps[3], "done");

    // Recipe 3: fruit salad (matched + unmatched + matched)
    initRecipe(&recipes[2], "fruit-salad", "dessert", 1);
    strcpy(recipes[2].ingredients[0].item, "apple");
    recipes[2].ingredients[0].quantity = 2.0f;
    strcpy(recipes[2].ingredients[0].unit, "pieces");
    strcpy(recipes[2].ingredients[1].item, "banana");  // unmatched
    recipes[2].ingredients[1].quantity = 1.0f;
    strcpy(recipes[2].ingredients[1].unit, "piece");
    strcpy(recipes[2].ingredients[2].item, "tomato");
    recipes[2].ingredients[2].quantity = 1.0f;
    strcpy(recipes[2].ingredients[2].unit, "piece");
    strcpy(recipes[2].ingredients[3].item, "honey");  // unmatched
    recipes[2].ingredients[3].quantity = 30.0f;
    strcpy(recipes[2].ingredients[3].unit, "grams");
    strcpy(recipes[2].ingredients[4].item, "done");

    strcpy(recipes[2].steps[0], "chop fruits");
    strcpy(recipes[2].steps[1], "mix in bowl");
    strcpy(recipes[2].steps[2], "drizzle honey");
    strcpy(recipes[2].steps[3], "done");

    // Recipe 4: simple pasta (matched + unmatched)
    initRecipe(&recipes[3], "pasta-simple", "main", 3);
    strcpy(recipes[3].ingredients[0].item, "pasta");
    recipes[3].ingredients[0].quantity = 300.0f;
    strcpy(recipes[3].ingredients[0].unit, "grams");
    strcpy(recipes[3].ingredients[1].item, "garlic");  // unmatched
    recipes[3].ingredients[1].quantity = 10.0f;
    strcpy(recipes[3].ingredients[1].unit, "grams");
    strcpy(recipes[3].ingredients[2].item, "olive-oil");  // unmatched
    recipes[3].ingredients[2].quantity = 20.0f;
    strcpy(recipes[3].ingredients[2].unit, "ml");
    strcpy(recipes[3].ingredients[3].item, "done");

    strcpy(recipes[3].steps[0], "boil water");
    strcpy(recipes[3].steps[1], "cook pasta");
    strcpy(recipes[3].steps[2], "toss with garlic and oil");
    strcpy(recipes[3].steps[3], "done");

    // Recipe 5: zero-calorie starter.
    initRecipe(&recipes[4], "hydration-shot", "starter", 1);
    strcpy(recipes[4].ingredients[0].item, "water");
    recipes[4].ingredients[0].quantity = 250.0f;
    strcpy(recipes[4].ingredients[0].unit, "ml");
    strcpy(recipes[4].ingredients[1].item, "done");
    strcpy(recipes[4].steps[0], "pour water");
    strcpy(recipes[4].steps[1], "done");

    // Recipe 6: zero-calorie dessert.
    initRecipe(&recipes[5], "cool-cucumber", "dessert", 1);
    strcpy(recipes[5].ingredients[0].item, "cucumber");
    recipes[5].ingredients[0].quantity = 100.0f;
    strcpy(recipes[5].ingredients[0].unit, "grams");
    strcpy(recipes[5].ingredients[1].item, "water");
    recipes[5].ingredients[1].quantity = 100.0f;
    strcpy(recipes[5].ingredients[1].unit, "ml");
    strcpy(recipes[5].ingredients[2].item, "done");
    strcpy(recipes[5].steps[0], "slice cucumber");
    strcpy(recipes[5].steps[1], "add water");
    strcpy(recipes[5].steps[2], "done");
}



int main(void)
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;
    int recipeCount = 0;

    seedFoods(foods, &foodCount);
    seedTestRecipes(recipes, &recipeCount);

    printf("\n=== RECOMMEND MENU FUNCTION TEST ===\n");
    printf("Loaded %d foods and %d recipes.\n\n", foodCount, recipeCount);
    printf("Expected behavior:\n");
    printf("- Recommend menu should work even with 0-calorie foods (water/cucumber).\n");
    printf("- With low target calories, zero-calorie recipes can still be recommended.\n");
    printf("- No crash when recipes include 0-calorie ingredients.\n\n");

    recommendMenu(recipes, recipeCount, foods, foodCount);

    return 0;
}
