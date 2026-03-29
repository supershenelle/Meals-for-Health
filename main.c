/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned. I have constructed the functions and their respective algorithms and corresponding 
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have 
not copied in part or whole or otherwise plagiarized the work of other students and/or persons, nor did I 
employ the use of AI in any part of the deliverable.

Nono, Shenelle Andrea - DLSU ID# 12505668
Yatco, Marco Alfredo - DLSU ID# 12504084
*********************************************************************************************************/

#include <stdio.h>
#include "functions.h"

int main()
{
    struct foodTag foods[50];
    struct recipeTag recipes[50];
    int foodCount = 0;
    int recipeCount = 0;

    shortString passKey = "ad1234";

    displayMain(foods, &foodCount, recipes, &recipeCount, passKey);

    return 0;
}
