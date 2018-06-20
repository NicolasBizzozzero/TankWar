#include "grille.h"


enum TypeCase** init_grille(void)
{
    // Allocation de l'espace memoire necessaire pour contenir la grille
    enum TypeCase** grille = (enum TypeCase**) malloc(sizeof(enum TypeCase*) * TAILLE_PLATEAU);
    int i;
    for (i=0; i < TAILLE_PLATEAU; i++) {
        grille[i] = (enum TypeCase*) malloc(sizeof(enum TypeCase) * TAILLE_PLATEAU);
    }

    // Ectriture de la carte a la main.
    // TODO: Trouver une facon plus automatique de le faire (eg: lire un fichier).
    grille[0][0] = BASE_VERTE;
    grille[0][1] = BASE_VERTE;
    grille[0][2] = BASE_VERTE;
    grille[0][3] = BASE_VERTE;
    grille[0][4] = BASE_VERTE;
    grille[0][5] = MINE;
    grille[0][6] = VIDE;
    grille[0][7] = VIDE;
    grille[0][8] = VIDE;
    grille[0][9] = VIDE;
    grille[0][10] = VIDE;
    grille[1][0] = BASE_VERTE;
    grille[1][1] = MINE;
    grille[1][2] = BASE_VERTE;
    grille[1][3] = BASE_VERTE;
    grille[1][4] = VIDE;
    grille[1][5] = VIDE;
    grille[1][6] = VIDE;
    grille[1][7] = VIDE;
    grille[1][8] = VIDE;
    grille[1][9] = MINE;
    grille[1][10] = VIDE;
    grille[2][0] = BASE_VERTE;
    grille[2][1] = BASE_VERTE;
    grille[2][2] = BASE_VERTE;
    grille[2][3] = MINE;
    grille[2][4] = VIDE;
    grille[2][5] = MINE;
    grille[2][6] = VIDE;
    grille[2][7] = MINE;
    grille[2][8] = VIDE;
    grille[2][9] = VIDE;
    grille[2][10] = VIDE;
    grille[3][0] = BASE_VERTE;
    grille[3][1] = BASE_VERTE;
    grille[3][2] = MINE;
    grille[3][3] = VIDE;
    grille[3][4] = VIDE;
    grille[3][5] = VIDE;
    grille[3][6] = VIDE;
    grille[3][7] = VIDE;
    grille[3][8] = MINE;
    grille[3][9] = VIDE;
    grille[3][10] = VIDE;
    grille[4][0] = BASE_VERTE;
    grille[4][1] = VIDE;
    grille[4][2] = VIDE;
    grille[4][3] = VIDE;
    grille[4][4] = POLLUEE;
    grille[4][5] = POLLUEE;
    grille[4][6] = POLLUEE;
    grille[4][7] = VIDE;
    grille[4][8] = VIDE;
    grille[4][9] = VIDE;
    grille[4][10] = VIDE;
    grille[5][0] = MINE;
    grille[5][1] = VIDE;
    grille[5][2] = MINE;
    grille[5][3] = VIDE;
    grille[5][4] = POLLUEE;
    grille[5][5] = POLLUEE;
    grille[5][6] = POLLUEE;
    grille[5][7] = VIDE;
    grille[5][8] = MINE;
    grille[5][9] = VIDE;
    grille[5][10] = MINE;
    grille[6][0] = VIDE;
    grille[6][1] = VIDE;
    grille[6][2] = VIDE;
    grille[6][3] = VIDE;
    grille[6][4] = POLLUEE;
    grille[6][5] = POLLUEE;
    grille[6][6] = POLLUEE;
    grille[6][7] = VIDE;
    grille[6][8] = VIDE;
    grille[6][9] = VIDE;
    grille[6][10] = BASE_BLEUE;
    grille[7][0] = VIDE;
    grille[7][1] = VIDE;
    grille[7][2] = MINE;
    grille[7][3] = VIDE;
    grille[7][4] = VIDE;
    grille[7][5] = VIDE;
    grille[7][6] = VIDE;
    grille[7][7] = VIDE;
    grille[7][8] = MINE;
    grille[7][9] = BASE_BLEUE;
    grille[7][10] = BASE_BLEUE;
    grille[8][0] = VIDE;
    grille[8][1] = VIDE;
    grille[8][2] = VIDE;
    grille[8][3] = MINE;
    grille[8][4] = VIDE;
    grille[8][5] = MINE;
    grille[8][6] = VIDE;
    grille[8][7] = MINE;
    grille[8][8] = BASE_BLEUE;
    grille[8][9] = BASE_BLEUE;
    grille[8][10] = BASE_BLEUE;
    grille[9][0] = VIDE;
    grille[9][1] = MINE;
    grille[9][2] = VIDE;
    grille[9][3] = VIDE;
    grille[9][4] = VIDE;
    grille[9][5] = VIDE;
    grille[9][6] = VIDE;
    grille[9][7] = BASE_BLEUE;
    grille[9][8] = BASE_BLEUE;
    grille[9][9] = MINE;
    grille[9][10] = BASE_BLEUE;
    grille[10][0] = VIDE;
    grille[10][1] = VIDE;
    grille[10][2] = VIDE;
    grille[10][3] = VIDE;
    grille[10][4] = VIDE;
    grille[10][5] = MINE;
    grille[10][6] = BASE_BLEUE;
    grille[10][7] = BASE_BLEUE;
    grille[10][8] = BASE_BLEUE;
    grille[10][9] = BASE_BLEUE;
    grille[10][10] = BASE_BLEUE;

    return grille;
}


char* get_case_char(enum TypeCase case_a_convertir, int x, int y, Tank** tanks_camp_vert, Tank** tanks_camp_bleu)
{
    int index_tank = 0;
    // On verifie si un tank commandant est present sur la case
    if (tank_est_sur_la_case(tanks_camp_vert[0], x, y) ||
        tank_est_sur_la_case(tanks_camp_bleu[0], x, y))
        return CHAR_TANK_COMMANDANT;

    // On verifie si un tank soldat est present sur la case
    for (index_tank=1; index_tank < NOMBRE_TANKS_INITIAUX; index_tank++) {
        if (tank_est_sur_la_case(tanks_camp_vert[index_tank], x, y) ||
            tank_est_sur_la_case(tanks_camp_bleu[index_tank], x, y))
            return CHAR_TANK_SOLDAT;
    }

    // Aucun objet deplacable n'est present sur la case, les objets immobiles etant deja representes par leur couleur.
    // On retourne donc du vide (un espace).
    return CHAR_VIDE;
}


int get_case_background_color(enum TypeCase case_a_convertir)
{
    switch (case_a_convertir) {
        case VIDE:
            return BACKGROUND_JAUNE;
        case MINE:
            return BACKGROUND_NOIR;
        case POLLUEE:
            return BACKGROUND_ROUGE;
        case BASE_VERTE:
            return BACKGROUND_VERT;
        case BASE_BLEUE:
            return BACKGROUND_BLEU;
        default:
            // Ne devrait jamais apparaitre
            exit(EXIT_FAILURE);
    }
}


int get_case_char_color(int x, int y, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, char* symbole,
                        int couleur_background)
{
    // On ne cherche a retourner qu'une couleur si la case contient un tank. On va donc utiliser le symbole
    // prealablement retourne.
    if ((symbole[0] != CHAR_TANK_COMMANDANT[0]) && (symbole[0] != CHAR_TANK_SOLDAT[0]))
        return couleur_background;

    // On cherche maintenant a savoir si ce tank est actuellement selectionne.
    Tank* tank;
    if ((tank = get_tank_by_position(tanks_camp_vert, x, y)) != NULL)
        return (tank->est_actuellement_selectionne == TRUE ? COLOR_CHAR_TANK_SELECTIONNE : COLOR_CHAR_TANK_NON_SELECTIONNE);
    else if ((tank = get_tank_by_position(tanks_camp_bleu, x, y)) != NULL)
        return (tank->est_actuellement_selectionne == TRUE ? COLOR_CHAR_TANK_SELECTIONNE : COLOR_CHAR_TANK_NON_SELECTIONNE);
    else
        // Ne devrait jamais arriver, si c'est le cas, alors la position donnee en parametre est eronnee
        exit(EXIT_FAILURE);
}
