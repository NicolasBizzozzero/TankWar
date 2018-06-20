#include "aleatoire.h"


/**
 * Retourne aleatoirement un entier entre `borne_min` inclus, et `borne_max`
 * exclus.
 */
int get_int_aleatoirement(int borne_min, int borne_max)
{
    srand(time(NULL));
    return rand() % (borne_max - borne_min) + borne_min;
}


/**
 * Retourne aleatoirement un entier du tableau `choix_possibles` passe en
 * parametre. Le `nombre_de_choix` correspond a la taille du tableau.
 */
int choice(int choix_possibles[], unsigned int nombre_de_choix)
{
    int index_choix = get_int_aleatoirement(0, nombre_de_choix);
    return choix_possibles[index_choix];
}
