# 🍽️ Food Calorie & Recipe Manager

> A console-based C program for managing food calorie entries and recipes — built as a Machine Project for **S11**.

**Authors:** Shenelle Nono & Marco Yatco  
**Section:** S11

---

## 📋 Overview

The Food Calorie & Recipe Manager is a menu-driven C application that allows users to log food calorie data, manage recipes, and generate useful outputs such as shopping lists and meal recommendations. The system is protected by a login system with two distinct modes of access.

---

## 🔐 Access Modes

| Mode | Description |
|------|-------------|
| **Update Mode** (`U`) | Authenticated mode for adding and modifying data |
| **Access Mode** (`A`) | Read-only mode for viewing and exporting data |
| **Exit** (`E`) | Exits the program |

Default credentials:
- **Username:** `admin`
- **Password:** `ad1234`

---

## ⚙️ Features

### 🥗 Food Calorie Management
- **Add** food entries with name, quantity, unit, and calories
- **View** food calorie entries (paginated, 10 per page)
- **Save** food entries to a `.txt` file
- **Load** food entries from a `.txt` file

### 📖 Recipe Management
- **Add** recipes with title, classification, servings, ingredients, and steps
- **Modify** recipes — add/delete ingredients and steps
- **Delete** recipes (case-insensitive)
- **List** recipes sorted alphabetically
- **Scan** through recipes one by one
- **Search** for a specific recipe by title
- **Export** recipes to a `.txt` file
- **Import** recipes from a `.txt` file

### 🛒 Additional Tools
- **Generate Shopping List** — scaled to a specified number of people
- **Scan by Ingredient** — find all recipes containing a specific ingredient
- **Calculate Recipe Calories** — auto-calculates based on logged food data
- **Recommend Menu** — suggests a starter, main course, and dessert within a target calorie budget
- **Change Password** — update login credentials securely

---

## 🗂️ Recipe Classifications

Valid recipe classifications:
- `breakfast`
- `lunch`
- `dinner`
- `main`
- `starter`
- `dessert`
- `snack` *(invalid — will be rejected)*

---

## 📐 Constraints

| Item | Limit |
|------|-------|
| Max ingredients per recipe | 20 |
| Max steps per recipe | 15 |
| Max food name/string length | 20 characters |
| Duplicate food/recipe names | Not allowed (case-insensitive) |

---

## 🧪 Testing

All functions were tested using a structured test script covering:
- ✅ Valid inputs and expected outputs
- ✅ Edge cases (empty lists, duplicates, invalid input)
- ✅ Boundary conditions (max ingredients, max steps, pagination)
- ✅ Case-insensitive matching across all search and delete operations

**All test cases passed (P).**

Key functions tested include:
`caseInsensitiveCompare`, `getValidIntInput`, `getString`, `changePassword`, `updateMode`, `accessMode`, `checkFoodName`, `checkRecipeTitle`, `addFoodCalories`, `viewFoodCalories`, `saveCalories`, `loadCalories`, `addRecipe`, `modifyRecipe`, `deleteRecipe`, `sortRecipes`, `listRecipe`, `searchRecipe`, `scanRecipe`, `exportRecipe`, `importRecipe`, `generateShoppingList`, `scanIngredient`, `recommendMenu`, `calculateRecipeCalories`, `displayRecipe`

---

## 👩‍💻 Authors

| Name | Section |
|------|---------|
| Shenelle Nono | S11 |
| Marco Yatco | S11 |
