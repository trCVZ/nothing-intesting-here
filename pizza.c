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
    printf("Pizza : %s\n", p->name);
    printf("Ingredients :\n");
    for (int i = 0; i < p->num_ingredients; i++) {
        if (p->ingredients[i].price != 0.00) {
            printf("  - %s : $%.2f\n", p->ingredients[i].name, p->ingredients[i].price);
        }
    }
    printf("Total price : $%.2f\n", p->price);
}

int add_ingredient(pizza* pizza, const char* ingredient_name) {
    if (pizza->num_ingredients >= MAX_INGREDIENTS) {
        return 0;
    }
    ingredient ing = find_ingredient_by_name(ingredient_name);
    if (strcmp(ing.name, "") == 0) {
        return 0;
    }

    int index = pizza->num_ingredients;
    pizza->ingredients[index] = ing;
    pizza->price += ing.price;
    pizza->num_ingredients++;
    return 1;
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

    printf("Pizza Deluxe contains 'Tomato Sauce' : %i\n", contains_ingredient(&pizza_deluxe, "Tomato Sauce"));
    printf("Pizza Deluxe contains 'Tomato Saue' :  %i\n", contains_ingredient(&pizza_deluxe, "Tomata Saue"));

    printf("Add Beef to Pizza Deluxe : ");
    printf("%i\n", add_ingredient(&pizza_deluxe, "Beef"));


    print_pizza(&pizza_deluxe);

    return 0;
}

// Liste des fonctions à ajouter

/*Ajouter un ingrédient : Une fonction pour ajouter un nouvel ingrédient à une pizza existante.
Supprimer un ingrédient : Une fonction pour supprimer un ingrédient d'une pizza existante.
Modifier le prix d'un ingrédient : Une fonction pour modifier le prix d'un ingrédient spécifique dans la liste des ingrédients.
Calculer le nombre total de calories : Une fonction pour calculer le nombre total de calories d'une pizza en fonction des calories de chaque ingrédient.
Rechercher une pizza par nom : Une fonction pour rechercher une pizza par son nom dans une liste de pizzas.
Lister toutes les pizzas : Une fonction pour afficher toutes les pizzas disponibles dans une liste.
Trier les pizzas par prix : Une fonction pour trier les pizzas par prix, du moins cher au plus cher.
Trier les pizzas par nombre d'ingrédients : Une fonction pour trier les pizzas par nombre d'ingrédients, de la plus simple à la plus complexe.
Calculer le coût moyen des ingrédients : Une fonction pour calculer le coût moyen des ingrédients d'une pizza.
Comparer deux pizzas : Une fonction pour comparer deux pizzas et déterminer laquelle est la plus chère ou laquelle a le plus d'ingrédients.
Sauvegarder les pizzas dans un fichier : Une fonction pour sauvegarder la liste des pizzas dans un fichier pour une utilisation ultérieure.
Charger les pizzas depuis un fichier : Une fonction pour charger la liste des pizzas depuis un fichier.
Calculer le prix total de toutes les pizzas : Une fonction pour calculer le prix total de toutes les pizzas dans une liste.
Filtrer les pizzas par ingrédient : Une fonction pour filtrer les pizzas qui contiennent un ingrédient spécifique.
Afficher les ingrédients uniques : Une fonction pour afficher tous les ingrédients uniques utilisés dans toutes les pizzas.
*/