#include <stdio.h>
#include <unistd.h>
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

static void runCheckFoodNameTests(void)
{
    struct foodTag foods[50];
    int foodCount;
    int actual;
    int passed = 0;
    int total = 0;

    seedFoods(foods, &foodCount);

    total++;
    actual = checkFoodName(foods, foodCount, "apple");
    if (actual == 1)
    {
        printf("[PASS] exact match returns correct index (apple -> 1)\n");
        passed++;
    }
    else
        printf("[FAIL] exact match expected 1, got %d\n", actual);

    total++;
    actual = checkFoodName(foods, foodCount, "ApPLe");
    if (actual == 1)
    {
        printf("[PASS] case-insensitive match works (ApPLe -> 1)\n");
        passed++;
    }
    else
        printf("[FAIL] case-insensitive match expected 1, got %d\n", actual);

    total++;
    actual = checkFoodName(foods, foodCount, "banana");
    if (actual == -1)
    {
        printf("[PASS] missing food returns -1\n");
        passed++;
    }
    else
        printf("[FAIL] missing food expected -1, got %d\n", actual);

    total++;
    actual = checkFoodName(foods, 0, "apple");
    if (actual == -1)
    {
        printf("[PASS] empty food list returns -1\n");
        passed++;
    }
    else
        printf("[FAIL] empty food list expected -1, got %d\n", actual);

    total++;
    strcpy(foods[7].name, "apple");
    foods[7].quantity = 1.0f;
    strcpy(foods[7].unit, "piece");
    foods[7].calories = 95.0f;
    foodCount = 8;

    actual = checkFoodName(foods, foodCount, "apple");
    if (actual == 7)
    {
        printf("[PASS] duplicate names return last matching index (apple -> 7)\n");
        passed++;
    }
    else
        printf("[FAIL] duplicate names expected 7, got %d\n", actual);

    printf("\ncheckFoodName tests: %d/%d passed.\n", passed, total);
}

static void runCheckRecipeTitleTests(void)
{
    struct recipeTag recipes[50];
    int recipeCount;
    int actual;
    int passed = 0;
    int total = 0;

    seedTestRecipes(recipes, &recipeCount);

    total++;
    actual = checkRecipeTitle(recipes, recipeCount, "chicken-rice");
    if (actual == 1)
    {
        printf("[PASS] exact title match returns correct index (chicken-rice -> 1)\n");
        passed++;
    }
    else
        printf("[FAIL] exact title match expected 1, got %d\n", actual);

    total++;
    actual = checkRecipeTitle(recipes, recipeCount, "ChIcKeN-RiCe");
    if (actual == 1)
    {
        printf("[PASS] case-insensitive title match works (ChIcKeN-RiCe -> 1)\n");
        passed++;
    }
    else
        printf("[FAIL] case-insensitive title match expected 1, got %d\n", actual);

    total++;
    actual = checkRecipeTitle(recipes, recipeCount, "adobo");
    if (actual == -1)
    {
        printf("[PASS] missing recipe title returns -1\n");
        passed++;
    }
    else
        printf("[FAIL] missing recipe title expected -1, got %d\n", actual);

    total++;
    actual = checkRecipeTitle(recipes, 0, "pasta-tomato");
    if (actual == -1)
    {
        printf("[PASS] empty recipe list returns -1\n");
        passed++;
    }
    else
        printf("[FAIL] empty recipe list expected -1, got %d\n", actual);

    total++;
    initRecipe(&recipes[6], "pasta-tomato", "main", 2);
    recipeCount = 7;

    actual = checkRecipeTitle(recipes, recipeCount, "pasta-tomato");
    if (actual == 6)
    {
        printf("[PASS] duplicate titles return last matching index (pasta-tomato -> 6)\n");
        passed++;
    }
    else
        printf("[FAIL] duplicate titles expected 6, got %d\n", actual);

    printf("\ncheckRecipeTitle tests: %d/%d passed.\n", passed, total);
}

static int runGetStringWithInput(const char *input, shortString out)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;

    if (tmp == NULL)
        return -1;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -1;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -1;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -1;
    }

    getString(out);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return 0;
}

static void runGetStringTests(void)
{
    shortString value;
    int passed = 0;
    int total = 0;

    total++;
    if (runGetStringWithInput("apple\n", value) == 0 && strcmp(value, "apple") == 0)
    {
        printf("[PASS] getString reads a normal word\n");
        passed++;
    }
    else
        printf("[FAIL] getString normal input expected 'apple', got '%s'\n", value);

    total++;
    if (runGetStringWithInput("   mango shake\n", value) == 0 && strcmp(value, "mango shake") == 0)
    {
        printf("[PASS] getString skips leading spaces and keeps internal spaces\n");
        passed++;
    }
    else
        printf("[FAIL] getString spaced input expected 'mango shake', got '%s'\n", value);

    total++;
    if (runGetStringWithInput("abcdefghijklmnopqrstuvwxyz\n", value) == 0
        && strcmp(value, "abcdefghijklmnopqrst") == 0)
    {
        printf("[PASS] getString truncates input to 20 characters\n");
        passed++;
    }
    else
        printf("[FAIL] getString truncation expected 'abcdefghijklmnopqrst', got '%s'\n", value);

    printf("\ngetString tests: %d/%d passed.\n", passed, total);
}

static int runGetChoiceWithInput(char choice,
                                 const char *input,
                                 struct foodTag foods[],
                                 int *foodCount,
                                 struct recipeTag recipes[],
                                 int *recipeCount)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;
    int result;

    if (tmp == NULL)
        return -999;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -999;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -999;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -999;
    }

    result = getChoice(choice, foods, foodCount, recipes, recipeCount);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return result;
}

static void runGetChoiceTests(void)
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;
    int recipeCount = 0;
    int actual;
    int passed = 0;
    int total = 0;

    seedFoods(foods, &foodCount);
    seedTestRecipes(recipes, &recipeCount);

    total++;
    actual = getChoice('E', foods, &foodCount, recipes, &recipeCount);
    if (actual == 0)
    {
        printf("[PASS] getChoice('E') returns 0 (exit)\n");
        passed++;
    }
    else
        printf("[FAIL] getChoice('E') expected 0, got %d\n", actual);

    total++;
    actual = getChoice('e', foods, &foodCount, recipes, &recipeCount);
    if (actual == 0)
    {
        printf("[PASS] getChoice('e') returns 0 (case-insensitive exit)\n");
        passed++;
    }
    else
        printf("[FAIL] getChoice('e') expected 0, got %d\n", actual);

    total++;
    actual = getChoice('X', foods, &foodCount, recipes, &recipeCount);
    if (actual == -1)
    {
        printf("[PASS] getChoice invalid option returns -1\n");
        passed++;
    }
    else
        printf("[FAIL] getChoice invalid option expected -1, got %d\n", actual);

    total++;
    actual = runGetChoiceWithInput('U', "a\na\n13\n", foods, &foodCount, recipes, &recipeCount);
    if (actual == -1)
    {
        printf("[PASS] getChoice('U') returns -1 after exiting update menu\n");
        passed++;
    }
    else
        printf("[FAIL] getChoice('U') expected -1 after update exit, got %d\n", actual);

    total++;
    actual = runGetChoiceWithInput('A', "8\n", foods, &foodCount, recipes, &recipeCount);
    if (actual == -1)
    {
        printf("[PASS] getChoice('A') returns -1 after exiting access menu\n");
        passed++;
    }
    else
        printf("[FAIL] getChoice('A') expected -1 after access exit, got %d\n", actual);

    printf("\ngetChoice tests: %d/%d passed.\n", passed, total);
}

static int runDisplayMainWithInput(const char *input,
                                   struct foodTag foods[],
                                   int *foodCount,
                                   struct recipeTag recipes[],
                                   int *recipeCount)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;

    if (tmp == NULL)
        return -1;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -1;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -1;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -1;
    }

    displayMain(foods, foodCount, recipes, recipeCount);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return 0;
}

static void runDisplayMainTests(void)
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount;
    int recipeCount;
    int expectedFoodCount;
    int expectedRecipeCount;
    int status;
    int passed = 0;
    int total = 0;

    total++;
    seedFoods(foods, &foodCount);
    seedTestRecipes(recipes, &recipeCount);
    expectedFoodCount = foodCount;
    expectedRecipeCount = recipeCount;

    status = runDisplayMainWithInput("E\n", foods, &foodCount, recipes, &recipeCount);
    if (status == 0 && foodCount == expectedFoodCount && recipeCount == expectedRecipeCount)
    {
        printf("[PASS] displayMain exits with E and preserves counts\n");
        passed++;
    }
    else
        printf("[FAIL] displayMain with E failed (status=%d, foods=%d, recipes=%d)\n", status, foodCount, recipeCount);

    total++;
    seedFoods(foods, &foodCount);
    seedTestRecipes(recipes, &recipeCount);
    expectedFoodCount = foodCount;
    expectedRecipeCount = recipeCount;

    status = runDisplayMainWithInput("X\nE\n", foods, &foodCount, recipes, &recipeCount);
    if (status == 0 && foodCount == expectedFoodCount && recipeCount == expectedRecipeCount)
    {
        printf("[PASS] displayMain retries after invalid input then exits on E\n");
        passed++;
    }
    else
        printf("[FAIL] displayMain invalid-then-E failed (status=%d, foods=%d, recipes=%d)\n", status, foodCount, recipeCount);

    total++;
    seedFoods(foods, &foodCount);
    seedTestRecipes(recipes, &recipeCount);
    expectedFoodCount = foodCount;
    expectedRecipeCount = recipeCount;

    status = runDisplayMainWithInput("A\n8\nE\n", foods, &foodCount, recipes, &recipeCount);
    if (status == 0 && foodCount == expectedFoodCount && recipeCount == expectedRecipeCount)
    {
        printf("[PASS] displayMain handles access menu exit then main exit\n");
        passed++;
    }
    else
        printf("[FAIL] displayMain via access menu failed (status=%d, foods=%d, recipes=%d)\n", status, foodCount, recipeCount);

    total++;
    seedFoods(foods, &foodCount);
    seedTestRecipes(recipes, &recipeCount);
    expectedFoodCount = foodCount;
    expectedRecipeCount = recipeCount;

    status = runDisplayMainWithInput("U\na\na\n13\nE\n", foods, &foodCount, recipes, &recipeCount);
    if (status == 0 && foodCount == expectedFoodCount && recipeCount == expectedRecipeCount)
    {
        printf("[PASS] displayMain handles update menu exit then main exit\n");
        passed++;
    }
    else
        printf("[FAIL] displayMain via update menu failed (status=%d, foods=%d, recipes=%d)\n", status, foodCount, recipeCount);

    printf("\ndisplayMain tests: %d/%d passed.\n", passed, total);
}

static float absDiff(float a, float b)
{
    float d = a - b;
    if (d < 0.0f)
        d = -d;
    return d;
}

static int runAddFoodCaloriesWithInput(const char *input,
                                       struct foodTag foods[],
                                       int *foodCount)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;

    if (tmp == NULL)
        return -1;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -1;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -1;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -1;
    }

    addFoodCalories(foods, foodCount);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return 0;
}

static void runAddFoodCaloriesTests(void)
{
    struct foodTag foods[50];
    int foodCount;
    int status;
    int originalCount;
    int newIndex;
    int passed = 0;
    int total = 0;

    total++;
    seedFoods(foods, &foodCount);
    originalCount = foodCount;

    status = runAddFoodCaloriesWithInput("banana\n2\npiece\n105\n", foods, &foodCount);
    newIndex = foodCount - 1;
    if (status == 0
        && foodCount == originalCount + 1
        && strcmp(foods[newIndex].name, "banana") == 0
        && absDiff(foods[newIndex].quantity, 2.0f) < 0.0001f
        && strcmp(foods[newIndex].unit, "piece") == 0
        && absDiff(foods[newIndex].calories, 105.0f) < 0.0001f)
    {
        printf("[PASS] addFoodCalories adds a valid new food entry\n");
        passed++;
    }
    else
        printf("[FAIL] addFoodCalories valid add failed (status=%d, count=%d)\n", status, foodCount);

    total++;
    seedFoods(foods, &foodCount);
    originalCount = foodCount;

    status = runAddFoodCaloriesWithInput("apple\npear\n1\npiece\n101\n", foods, &foodCount);
    newIndex = foodCount - 1;
    if (status == 0
        && foodCount == originalCount + 1
        && strcmp(foods[newIndex].name, "pear") == 0
        && absDiff(foods[newIndex].quantity, 1.0f) < 0.0001f
        && strcmp(foods[newIndex].unit, "piece") == 0
        && absDiff(foods[newIndex].calories, 101.0f) < 0.0001f)
    {
        printf("[PASS] addFoodCalories retries when name already exists\n");
        passed++;
    }
    else
        printf("[FAIL] addFoodCalories duplicate-name retry failed (status=%d, count=%d)\n", status, foodCount);

    total++;
    seedFoods(foods, &foodCount);
    originalCount = foodCount;

    status = runAddFoodCaloriesWithInput("kiwi\n0\n2.5\npiece\n42\n", foods, &foodCount);
    newIndex = foodCount - 1;
    if (status == 0
        && foodCount == originalCount + 1
        && strcmp(foods[newIndex].name, "kiwi") == 0
        && absDiff(foods[newIndex].quantity, 2.5f) < 0.0001f
        && strcmp(foods[newIndex].unit, "piece") == 0
        && absDiff(foods[newIndex].calories, 42.0f) < 0.0001f)
    {
        printf("[PASS] addFoodCalories retries non-positive quantity until valid\n");
        passed++;
    }
    else
        printf("[FAIL] addFoodCalories non-positive quantity retry failed (status=%d, count=%d)\n", status, foodCount);

    printf("\naddFoodCalories tests: %d/%d passed.\n", passed, total);
}

static int runAddRecipeWithInput(const char *input,
                                 struct recipeTag recipes[],
                                 int *recipeCount)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;

    if (tmp == NULL)
        return -1;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -1;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -1;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -1;
    }

    addRecipe(recipes, recipeCount);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return 0;
}

static void runAddRecipeTests(void)
{
    struct recipeTag recipes[50];
    int recipeCount;
    int status;
    int idx;
    int passed = 0;
    int total = 0;

    total++;
    recipeCount = 0;
    status = runAddRecipeWithInput(
        "garlic rice\n"
        "main\n"
        "2\n"
        "rice\n"
        "1.5\n"
        "cup\n"
        "garlic\n"
        "3\n"
        "cloves\n"
        "done\n"
        "cook rice\n"
        "fry garlic\n"
        "mix together\n"
        "done\n",
        recipes,
        &recipeCount);
    idx = recipeCount - 1;
    if (status == 0
        && recipeCount == 1
        && strcmp(recipes[idx].title, "garlic rice") == 0
        && strcmp(recipes[idx].classification, "main") == 0
        && recipes[idx].servings == 2
        && recipes[idx].ingredientCount == 2
        && strcmp(recipes[idx].ingredients[0].item, "rice") == 0
        && absDiff(recipes[idx].ingredients[0].quantity, 1.5f) < 0.0001f
        && strcmp(recipes[idx].ingredients[0].unit, "cup") == 0
        && strcmp(recipes[idx].ingredients[1].item, "garlic") == 0
        && absDiff(recipes[idx].ingredients[1].quantity, 3.0f) < 0.0001f
        && strcmp(recipes[idx].ingredients[1].unit, "cloves") == 0
        && recipes[idx].stepCount == 3
        && strcmp(recipes[idx].steps[0], "cook rice") == 0
        && strcmp(recipes[idx].steps[1], "fry garlic") == 0
        && strcmp(recipes[idx].steps[2], "mix together") == 0)
    {
        printf("[PASS] addRecipe adds complete recipe with ingredients and steps\n");
        passed++;
    }
    else
        printf("[FAIL] addRecipe complete recipe add failed (status=%d, count=%d)\n", status, recipeCount);

    total++;
    recipeCount = 0;
    status = runAddRecipeWithInput(
        "fruit cup\n"
        "snack\n"
        "dessert\n"
        "1\n"
        "apple\n"
        "1\n"
        "piece\n"
        "done\n"
        "slice apple\n"
        "serve\n"
        "done\n",
        recipes,
        &recipeCount);
    idx = recipeCount - 1;
    if (status == 0
        && recipeCount == 1
        && strcmp(recipes[idx].classification, "dessert") == 0
        && recipes[idx].ingredientCount == 1
        && recipes[idx].stepCount == 2)
    {
        printf("[PASS] addRecipe retries invalid classification until valid\n");
        passed++;
    }
    else
        printf("[FAIL] addRecipe classification retry failed (status=%d, count=%d)\n", status, recipeCount);

    total++;
    recipeCount = 0;
    status = runAddRecipeWithInput(
        "water\n"
        "starter\n"
        "1\n"
        "done\n"
        "done\n",
        recipes,
        &recipeCount);
    idx = recipeCount - 1;
    if (status == 0
        && recipeCount == 1
        && recipes[idx].ingredientCount == 0
        && recipes[idx].stepCount == 0)
    {
        printf("[PASS] addRecipe handles immediate done for ingredients and steps\n");
        passed++;
    }
    else
        printf("[FAIL] addRecipe immediate-done flow failed (status=%d, count=%d)\n", status, recipeCount);

    printf("\naddRecipe tests: %d/%d passed.\n", passed, total);
}

static void seedIngredientStepRecipe(struct recipeTag recipes[], int index)
{
    initRecipe(&recipes[index], "test-recipe", "main", 2);

    strcpy(recipes[index].ingredients[0].item, "onion");
    recipes[index].ingredients[0].quantity = 1.0f;
    strcpy(recipes[index].ingredients[0].unit, "pc");

    strcpy(recipes[index].ingredients[1].item, "garlic");
    recipes[index].ingredients[1].quantity = 2.0f;
    strcpy(recipes[index].ingredients[1].unit, "cloves");

    strcpy(recipes[index].ingredients[2].item, "salt");
    recipes[index].ingredients[2].quantity = 0.5f;
    strcpy(recipes[index].ingredients[2].unit, "tsp");

    recipes[index].ingredientCount = 3;

    strcpy(recipes[index].steps[0], "prep ingredients");
    strcpy(recipes[index].steps[1], "cook aromatics");
    strcpy(recipes[index].steps[2], "season and finish");
    recipes[index].stepCount = 3;
}

static void runCheckIngredientTests(void)
{
    struct recipeTag recipes[50];
    int actual;
    int passed = 0;
    int total = 0;

    seedIngredientStepRecipe(recipes, 0);

    total++;
    actual = checkIngredient("onion", recipes, 0);
    if (actual == 0)
    {
        printf("[PASS] checkIngredient finds first ingredient index\n");
        passed++;
    }
    else
        printf("[FAIL] checkIngredient first index expected 0, got %d\n", actual);

    total++;
    actual = checkIngredient("GARLIC", recipes, 0);
    if (actual == 1)
    {
        printf("[PASS] checkIngredient is case-insensitive\n");
        passed++;
    }
    else
        printf("[FAIL] checkIngredient case-insensitive expected 1, got %d\n", actual);

    total++;
    actual = checkIngredient("pepper", recipes, 0);
    if (actual == -1)
    {
        printf("[PASS] checkIngredient returns -1 when missing\n");
        passed++;
    }
    else
        printf("[FAIL] checkIngredient missing expected -1, got %d\n", actual);

    printf("\ncheckIngredient tests: %d/%d passed.\n", passed, total);
}

static void runDeleteIngredientTests(void)
{
    struct recipeTag recipes[50];
    int passed = 0;
    int total = 0;

    total++;
    seedIngredientStepRecipe(recipes, 0);
    deleteIngredient("garlic", recipes, 0);
    if (recipes[0].ingredientCount == 2
        && strcmp(recipes[0].ingredients[0].item, "onion") == 0
        && strcmp(recipes[0].ingredients[1].item, "salt") == 0
        && recipes[0].ingredients[2].item[0] == '\0')
    {
        printf("[PASS] deleteIngredient removes middle ingredient and shifts left\n");
        passed++;
    }
    else
        printf("[FAIL] deleteIngredient middle removal produced incorrect state\n");

    total++;
    seedIngredientStepRecipe(recipes, 0);
    deleteIngredient("pepper", recipes, 0);
    if (recipes[0].ingredientCount == 3
        && strcmp(recipes[0].ingredients[0].item, "onion") == 0
        && strcmp(recipes[0].ingredients[1].item, "garlic") == 0
        && strcmp(recipes[0].ingredients[2].item, "salt") == 0)
    {
        printf("[PASS] deleteIngredient keeps recipe unchanged when item not found\n");
        passed++;
    }
    else
        printf("[FAIL] deleteIngredient changed data for missing ingredient\n");

    printf("\ndeleteIngredient tests: %d/%d passed.\n", passed, total);
}

static void runDeleteStepTests(void)
{
    struct recipeTag recipes[50];
    int passed = 0;
    int total = 0;

    total++;
    seedIngredientStepRecipe(recipes, 0);
    deleteStep(2, recipes, 0);
    if (recipes[0].stepCount == 2
        && strcmp(recipes[0].steps[0], "prep ingredients") == 0
        && strcmp(recipes[0].steps[1], "season and finish") == 0
        && recipes[0].steps[2][0] == '\0')
    {
        printf("[PASS] deleteStep removes selected step and shifts remaining steps\n");
        passed++;
    }
    else
        printf("[FAIL] deleteStep removal produced incorrect state\n");

    total++;
    seedIngredientStepRecipe(recipes, 0);
    deleteStep(1, recipes, 0);
    if (recipes[0].stepCount == 2
        && strcmp(recipes[0].steps[0], "cook aromatics") == 0
        && strcmp(recipes[0].steps[1], "season and finish") == 0)
    {
        printf("[PASS] deleteStep handles first-step deletion\n");
        passed++;
    }
    else
        printf("[FAIL] deleteStep first-step deletion incorrect\n");

    printf("\ndeleteStep tests: %d/%d passed.\n", passed, total);
}

static void seedSequentialFoods(struct foodTag foods[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        snprintf(foods[i].name, sizeof(foods[i].name), "food%02d", i + 1);
        foods[i].quantity = (float)(i + 1);
        strcpy(foods[i].unit, "unit");
        foods[i].calories = (float)(i * 10 + 5);
    }
}

static int foodsMatch(const struct foodTag left[], const struct foodTag right[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(left[i].name, right[i].name) != 0)
            return 0;
        if (strcmp(left[i].unit, right[i].unit) != 0)
            return 0;
        if (absDiff(left[i].quantity, right[i].quantity) > 0.0001f)
            return 0;
        if (absDiff(left[i].calories, right[i].calories) > 0.0001f)
            return 0;
    }

    return 1;
}

static int runViewFoodCaloriesWithInput(const char *input,
                                        struct foodTag foods[],
                                        int foodCount)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;

    if (tmp == NULL)
        return -1;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -1;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -1;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -1;
    }

    viewFoodCalories(foods, foodCount);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return 0;
}

static void runViewFoodCaloriesTests(void)
{
    struct foodTag foods[50];
    struct foodTag before[50];
    int foodCount;
    int status;
    int passed = 0;
    int total = 0;

    total++;
    foodCount = 0;
    status = runViewFoodCaloriesWithInput("", foods, foodCount);
    if (status == 0)
    {
        printf("[PASS] viewFoodCalories handles empty list\n");
        passed++;
    }
    else
        printf("[FAIL] viewFoodCalories empty-list run failed (status=%d)\n", status);

    total++;
    seedFoods(foods, &foodCount);
    memcpy(before, foods, sizeof(before));
    status = runViewFoodCaloriesWithInput("", foods, foodCount);
    if (status == 0 && foodsMatch(before, foods, foodCount))
    {
        printf("[PASS] viewFoodCalories single-page view preserves data\n");
        passed++;
    }
    else
        printf("[FAIL] viewFoodCalories single-page data changed or run failed\n");

    total++;
    seedSequentialFoods(foods, 11);
    foodCount = 11;
    memcpy(before, foods, sizeof(before));
    status = runViewFoodCaloriesWithInput("x\n", foods, foodCount);
    if (status == 0 && foodsMatch(before, foods, foodCount))
    {
        printf("[PASS] viewFoodCalories multi-page first prompt exit works\n");
        passed++;
    }
    else
        printf("[FAIL] viewFoodCalories first prompt exit failed or data changed\n");

    total++;
    seedSequentialFoods(foods, 21);
    foodCount = 21;
    memcpy(before, foods, sizeof(before));
    status = runViewFoodCaloriesWithInput("N\nX\n", foods, foodCount);
    if (status == 0 && foodsMatch(before, foods, foodCount))
    {
        printf("[PASS] viewFoodCalories page navigation (N then X) works\n");
        passed++;
    }
    else
        printf("[FAIL] viewFoodCalories page navigation failed or data changed\n");

    printf("\nviewFoodCalories tests: %d/%d passed.\n", passed, total);
}

static int runNextFoodEntryWithInput(const char *input, char *result)
{
    FILE *tmp = tmpfile();
    int savedStdinFd;

    if (tmp == NULL)
        return -1;

    if (fputs(input, tmp) < 0)
    {
        fclose(tmp);
        return -1;
    }

    rewind(tmp);
    savedStdinFd = dup(fileno(stdin));
    if (savedStdinFd < 0)
    {
        fclose(tmp);
        return -1;
    }

    if (dup2(fileno(tmp), fileno(stdin)) < 0)
    {
        close(savedStdinFd);
        fclose(tmp);
        return -1;
    }

    *result = nextFoodEntry(25);

    dup2(savedStdinFd, fileno(stdin));
    close(savedStdinFd);
    fclose(tmp);
    return 0;
}

static void runNextFoodEntryTests(void)
{
    char result;
    int status;
    int passed = 0;
    int total = 0;

    total++;
    status = runNextFoodEntryWithInput("N\n", &result);
    if (status == 0 && result == 'N')
    {
        printf("[PASS] nextFoodEntry accepts uppercase N\n");
        passed++;
    }
    else
        printf("[FAIL] nextFoodEntry uppercase N expected 'N', got '%c'\n", result);

    total++;
    status = runNextFoodEntryWithInput("x\n", &result);
    if (status == 0 && result == 'x')
    {
        printf("[PASS] nextFoodEntry accepts lowercase x\n");
        passed++;
    }
    else
        printf("[FAIL] nextFoodEntry lowercase x expected 'x', got '%c'\n", result);

    total++;
    status = runNextFoodEntryWithInput("q\nN\n", &result);
    if (status == 0 && result == 'N')
    {
        printf("[PASS] nextFoodEntry retries after invalid input then accepts valid choice\n");
        passed++;
    }
    else
        printf("[FAIL] nextFoodEntry invalid-then-valid expected 'N', got '%c'\n", result);

    printf("\nnextFoodEntry tests: %d/%d passed.\n", passed, total);
}



int main(void)
{
    printf("\n=== checkFoodName FUNCTION TESTS ===\n\n");
    runCheckFoodNameTests();

    printf("\n=== checkRecipeTitle FUNCTION TESTS ===\n\n");
    runCheckRecipeTitleTests();

    printf("\n=== getString FUNCTION TESTS ===\n\n");
    runGetStringTests();

    printf("\n=== getChoice FUNCTION TESTS ===\n\n");
    runGetChoiceTests();

    printf("\n=== displayMain FUNCTION TESTS ===\n\n");
    runDisplayMainTests();

    printf("\n=== addFoodCalories FUNCTION TESTS ===\n\n");
    runAddFoodCaloriesTests();

    printf("\n=== addRecipe FUNCTION TESTS ===\n\n");
    runAddRecipeTests();

    printf("\n=== checkIngredient FUNCTION TESTS ===\n\n");
    runCheckIngredientTests();

    printf("\n=== deleteIngredient FUNCTION TESTS ===\n\n");
    runDeleteIngredientTests();

    printf("\n=== deleteStep FUNCTION TESTS ===\n\n");
    runDeleteStepTests();

    printf("\n=== viewFoodCalories FUNCTION TESTS ===\n\n");
    runViewFoodCaloriesTests();

    printf("\n=== nextFoodEntry FUNCTION TESTS ===\n\n");
    runNextFoodEntryTests();

    return 0;
}
