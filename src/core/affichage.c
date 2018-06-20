#include "affichage.h"


void set_titre_fenetre(char* titre)
{
    SetConsoleTitle(_T(titre));
}


void appuyez_sur_une_touche_pour_continuer(void)
{
    printf("Appuyez sur une touche pour continuer.\n");
    _getch();
}


void clear_screen(void)
{
    system("cls");
}


void print_ecran_principal(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                           enum Camp joueur_actuel)
{
    clear_screen();
    printf("Appuyez sur [F1] pour quitter.\n");
    print_separation();
    print_scores(grille, tanks_camp_vert, tanks_camp_bleu);
    print_separation();
    printf("Au tour du camp %s :\n", camp_to_str(joueur_actuel));
    print_separation();
    print_grille(grille, tanks_camp_vert, tanks_camp_bleu);
    print_separation();
}


void print_scores(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu)
{
    printf(" | Camp VERT : %d | Camp BLEU : %d |\n", get_score_equipe(VERT, grille, tanks_camp_vert),
                                                     get_score_equipe(BLEU, grille, tanks_camp_bleu));
}


void print_selection_tank(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                          enum Camp joueur_actuel, Tank** tanks)
{
    print_ecran_principal(grille, tanks_camp_vert, tanks_camp_bleu, joueur_actuel);
    print_tanks(tanks);
    print_separation();
}


void print_selection_direction(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                               enum Camp joueur_actuel, Tank** tanks, enum Direction direction)
{
    print_selection_tank(grille, tanks_camp_vert, tanks_camp_bleu, joueur_actuel, tanks);
    print_direction(direction);
    print_separation();
}


void print_selection_profondeur(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                                enum Camp joueur_actuel, Tank** tanks, Tank* tank, enum Direction direction,
                                int profondeur, int profondeur_max)
{
    print_selection_direction(grille, tanks_camp_vert, tanks_camp_bleu, joueur_actuel, tanks, direction);
    print_profondeur(profondeur, profondeur_max);
    print_separation();
}


void print_separation(void)
{
    printf("%s\n", string_repeat(" ", LARGEUR_SEPARATION));
    printf("%s\n", string_repeat("=", LARGEUR_SEPARATION));
    printf("%s\n", string_repeat(" ", LARGEUR_SEPARATION));
}


void print_tanks(Tank** tanks)
{
    char* separateur = " | ";

    // On affiche tous les tanks du tableau
    int i;
    Tank* tank;
    char* char_tank;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        printf(separateur);

        // On recupere le tank et son symbole
        tank = tanks[i];
        char_tank = tank_to_str(tank);

        // Si le tank est mort, on affiche du vide
        if (tank->est_mort == TRUE) {
            printf(" ");
        }
        // Si le tank est actuellement selectionne, on le souligne
        else if (tank->est_actuellement_selectionne == TRUE) {
            print_texte_souligne(char_tank);
        } else {
            printf(char_tank);
        }
    }
    printf("%s\n", separateur);
}


void print_grille(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu)
{
    int x, y;
    enum TypeCase case_actuelle;
    for (y=0; y < TAILLE_PLATEAU; y++) {
        for (x=0; x < TAILLE_PLATEAU; x++) {
            case_actuelle = grille[y][x];
            char* symbole = get_case_char(case_actuelle, x, y, tanks_camp_vert, tanks_camp_bleu);
            int couleur_background = get_case_background_color(case_actuelle);
            int couleur_symbole = get_case_char_color(x, y, tanks_camp_vert, tanks_camp_bleu, symbole,
                                                      couleur_background);
            print_couleur(symbole, couleur_symbole, couleur_background);
        }
        printf("\n");
    }
}


void print_direction(enum Direction direction)
{
    char* separateur = " | ";

    printf(separateur);
    if (direction == NORD)
        print_texte_souligne(direction_to_str(NORD));
    else
        printf(direction_to_str(NORD));
    printf(separateur);
    if (direction == EST)
        print_texte_souligne(direction_to_str(EST));
    else
        printf(direction_to_str(EST));
    printf(separateur);
    if (direction == SUD)
        print_texte_souligne(direction_to_str(SUD));
    else
        printf(direction_to_str(SUD));
    printf(separateur);
    if (direction == OUEST)
        print_texte_souligne(direction_to_str(OUEST));
    else
        printf(direction_to_str(OUEST));
    printf(separateur);
    printf("\n");
}


void print_profondeur(int profondeur, int profondeur_max)
{
    char* separateur = " | ";

    printf(separateur);
    int i;
    for (i=0; i <= profondeur_max; i++) {
        if (i == profondeur) {
            // Conversion de i en string
            char buffer[2];
            itoa(i, buffer, 10);

            print_texte_souligne(buffer);
        } else
            printf("%d", i);
        printf(separateur);
    }

    printf("\n");
}


Tank* selection_tank(enum TypeCase** grille, Tank** tanks)
{
    int index_tank_selectionne = get_index_tank_actuellement_selectionne(tanks);
    Tank* tank_selectionne = tanks[index_tank_selectionne];

    int input = _getch();
    if (input == 0 || input == 224) {
        // L'utilisateur a entree une touche de fonction ou une fleche
        switch (input = _getch()) {
            case KEY_ARROW_LEFT:
                tank_selectionne->est_actuellement_selectionne = FALSE;

                // Calcul du nouvel index (pour empecher le depassement d'indice du tableau
                index_tank_selectionne = (index_tank_selectionne == 0 ? NOMBRE_TANKS_INITIAUX - 1 : index_tank_selectionne - 1);
                tanks[index_tank_selectionne]->est_actuellement_selectionne = TRUE;
                return NULL;

            case KEY_ARROW_RIGHT:
                tank_selectionne->est_actuellement_selectionne = FALSE;

                // Calcul du nouvel index (pour empecher le depassement d'indice du tableau
                index_tank_selectionne = (index_tank_selectionne == NOMBRE_TANKS_INITIAUX - 1 ? 0 : index_tank_selectionne + 1);
                tanks[index_tank_selectionne]->est_actuellement_selectionne = TRUE;
                return NULL;

            case KEY_EXIT:
                exit(0);

            default:
                return NULL;
        }
    } else if (input == KEY_ENTER) {
        // L'utilisateur a appuye sur entree
        return tank_selectionne;
    }

    return NULL;
}


int selection_direction(enum Direction* direction)
{
    int input = _getch();
    if (input == 0 || input == 224) {
        // L'utilisateur a entree une touche de fonction ou une fleche
        switch (input = _getch()) {
            case KEY_ARROW_LEFT:
                *direction = get_direction_gauche(*direction);
                return FALSE;

            case KEY_ARROW_RIGHT:
                *direction = get_direction_droite(*direction);
                return FALSE;

            case KEY_EXIT:
                exit(0);

            default:
                return FALSE;
        }
    } else if (input == KEY_ENTER) {
        // L'utilisateur a appuye sur entree
        return TRUE;
    }

    return FALSE;
}


int selection_profondeur(int* profondeur, int profondeur_max)
{
    int input = _getch();
    if (input == 0 || input == 224) {
        // L'utilisateur a entree une touche de fonction ou une fleche
        switch (input = _getch()) {
            case KEY_ARROW_LEFT:
                *profondeur = ((*profondeur) == 0 ? profondeur_max : (*profondeur) - 1);
                return FALSE;

            case KEY_ARROW_RIGHT:
                *profondeur = ((*profondeur) == profondeur_max ? 0 : (*profondeur) + 1);
                return FALSE;

            case KEY_EXIT:
                exit(0);

            default:
                return FALSE;
        }
    } else if (input == KEY_ENTER) {
        // L'utilisateur a appuye sur entree
        return TRUE;
    }

    return FALSE;
}

