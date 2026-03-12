#include <stdio.h>
#include "functions.h"

// =====================================================================================================
// TEST FUNCTION FOR VIEW FOOD CALORIES
#define MAX_FOODS 50

static void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

static void generateTestFoods(struct foodTag foods[], int *foodCount)
{
    int n, i;

    printf("Enter number of test foods (0-%d): ", MAX_FOODS);
    while (scanf(" %d", &n) != 1 || n < 0 || n > MAX_FOODS)
    {
        printf("Invalid input. Enter 0-%d: ", MAX_FOODS);
        clearInputBuffer();
    }

    *foodCount = n;

    for (i = 0; i < n; i++)
    {
        // jumbled-looking short names
        snprintf(foods[i].name, sizeof(foods[i].name), "xq%dz%d", i + 1, (i * 7) % 97);
        foods[i].quantity = (float)((i % 9) + 1) * 10.0f;
        strcpy(foods[i].unit, "grams");
        foods[i].calories = 80.0f + (float)((i * 13) % 250);
    }
}

int main(void)
{
    char again = 'Y';

    while (again == 'Y' || again == 'y')
    {
        addRecipe();

        printf("\nTest add recipe again? (Y/N): ");
        scanf(" %c", &again);
    }

    return 0;
}
