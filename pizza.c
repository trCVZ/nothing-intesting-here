#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_INGREDIENTS 10
#define MAX_NAME_LENGTH 20

typedef struct ingredient {
    char name[MAX_NAME_LENGTH];
    float price;
} ingredient;

typedef struct pizza {
    ingredient ingredients[MAX_INGREDIENTS];
    float price;
    char name[MAX_NAME_LENGTH];
    int num_ingredients;
} pizza;

const ingredient ingredient_list[] = {
    {"Tomato Sauce", 0.5},
    {"Chicken", 2.00},
    {"Arugula", 1.00},
    {"Goat Cheese", 1.50},
    {"Beef", 2.50}
};

ingredient find_ingredient_by_name(const char* name) {
    for (size_t i = 0; i < sizeof(ingredient_list) / sizeof(ingredient_list[0]); i++) {
        if (strcmp(ingredient_list[i].name, name) == 0) {
            return ingredient_list[i];
        }
    }
    ingredient not_found = { "", 0.0 };
    return not_found;
}

void init_pizza(pizza* pizza, const char* name, const char* ingredient_names[], size_t num_ingredients) {
    if (num_ingredients > MAX_INGREDIENTS) {
        num_ingredients = MAX_INGREDIENTS;
    }

    strncpy(pizza->name, name, MAX_NAME_LENGTH - 1);
    pizza->name[MAX_NAME_LENGTH - 1] = '\0';

    pizza->price = 0.0;
    pizza->num_ingredients = 0;

    for (size_t i = 0; i < num_ingredients; i++) {
        ingredient ing = find_ingredient_by_name(ingredient_names[i]);
        if (ing.price != 0.0) {
            pizza->ingredients[i] = ing;
            pizza->price += ing.price;
            pizza->num_ingredients++;
        }
    }

    pizza->price = roundf(pizza->price * 100) / 100;
}

int contains_ingredient(const pizza* pizza, const char* ingredient) {
    for (size_t i = 0; i < sizeof(pizza->ingredients) / sizeof(pizza->ingredients[0]); i++) {
        if (strcmp(pizza->ingredients[i].name, ingredient) == 0) {
            return 1;
        }
    }
    return 0;
}

void print_pizza(const pizza* p) {
    printf("Pizza: %s\n", p->name);
    printf("Ingredients:\n");
    for (int i = 0; i < p->num_ingredients; i++) {
        if (p->ingredients[i].price != 0.00) {
            printf("  - %s: $%.2f\n", p->ingredients[i].name, p->ingredients[i].price);
        }
    }
    printf("Total price: $%.2f\n", p->price);
}

int main() {
    pizza pizza_deluxe;
    const char* selected_ingredients[] = {
        "Tomato Sauce",
        "Chicken",
        "Goat Cheese",
    };
    size_t num_selected_ingredients = sizeof(selected_ingredients) / sizeof(selected_ingredients[0]);

    init_pizza(&pizza_deluxe, "Deluxe", selected_ingredients, num_selected_ingredients);
    print_pizza(&pizza_deluxe);

    printf("%i\n", contains_ingredient(&pizza_deluxe, "Tomato Sauce"));
    printf("%i", contains_ingredient(&pizza_deluxe, "Tomata Saue"));
    return 0;
}