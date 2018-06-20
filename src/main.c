#include <stdio.h>
#include <stdlib.h>
#include "common/boolean.h"
#include "core/grille.h"
#include "core/affichage.h"
#include "core/jeu.h"
#include "core/tank.h"
#define TITRE_FENETRE "TankWar"


int main()
{
    // Debut du jeu
    printf("Le jeu commence !\n");
    set_titre_fenetre(TITRE_FENETRE);

    // Initialisation du jeu
    Tank** tanks_camp_vert = init_tanks_camp_vert();
    Tank** tanks_camp_bleu = init_tanks_camp_bleu();
    enum TypeCase** grille = init_grille();

    // Tirage au sort du premier joueur
    enum Camp joueur_actuel = tirage_au_sort_premier_joueur();

    // Boucle principale
    Tank** tanks;
    Tank** tanks_adverses;
    while (jeu_fini(grille, tanks_camp_vert, tanks_camp_bleu) == FALSE) {
        tanks = (joueur_actuel == VERT ? tanks_camp_vert : tanks_camp_bleu);
        tanks_adverses = (joueur_actuel == VERT ? tanks_camp_bleu : tanks_camp_vert);
        set_first_tank_alive_as_currently_selectionned(tanks);

        // Selection du tank qui va avancer
        Tank* tank = NULL;
        do {
            print_selection_tank(grille, tanks_camp_vert, tanks_camp_bleu, joueur_actuel, tanks);
            tank = selection_tank(grille, tanks);
            tank_coince(grille, tanks_camp_vert, tanks_camp_bleu, tank);
        } while (tank == NULL);

        // Selection de la direction dans laquelle avancer
        enum Direction direction = NORD;
        do {
            print_selection_direction(grille, tanks_camp_vert, tanks_camp_bleu, joueur_actuel, tanks, direction);
        } while (selection_direction(&direction) != TRUE);

        // Selection de la profondeur a laquelle avancer
        int profondeur = 0;
        int profondeur_max = get_profondeur_max(grille, tanks_camp_vert, tanks_camp_bleu, tank, direction);
        do {
            print_selection_profondeur(grille, tanks_camp_vert, tanks_camp_bleu, joueur_actuel, tanks, tank, direction,
                                       profondeur, profondeur_max);
        } while (selection_profondeur(&profondeur, profondeur_max) != TRUE);

        // On avance le tank !
        deplace_tank(grille, tanks_adverses, tank, direction, profondeur);

        // Au tour de l'autre joueur
        joueur_actuel = camp_adverse(joueur_actuel);
    }

    return EXIT_SUCCESS;
}
