#ifndef TANKWAR_GRILLE_H
#define TANKWAR_GRILLE_H


#include <stdlib.h>
#include "../common/couleurs.h"
#include "../common/boolean.h"
#include "tank.h"
#include "case.h"
#define TAILLE_PLATEAU 11
#define CHAR_VIDE " "
#define COLOR_CHAR_TANK_SELECTIONNE FOREGROUND_VIOLET
#define COLOR_CHAR_TANK_NON_SELECTIONNE 7


/**
 * Initialise une grille puis la retourne.
 * La grille retournee ressemblera exactement a celle decrite dans l'enonce.
 * @return La grille initialisee.
 */
enum TypeCase** init_grille(void);


/**
 * Converti une case vers le caractere la representant au mieux.
 * @param case_a_convertir, la case a convertir.
 * @param x, l'abscisse de la case qu'on convertit.
 * @param y, l'ordonnee de la case qu'on convertit.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 * @return le caractere correspondant au mieux a la case.
 */
char* get_case_char(enum TypeCase case_a_convertir, int x, int y, Tank** tanks_camp_vert, Tank** tanks_camp_bleu);


/**
 * Recupere la couleur du background d'une case selon son contenu.
 * @param case_a_convertir, la case a convertir.
 * @return la couleur correspondant a la case.
 */
int get_case_background_color(enum TypeCase case_a_convertir);


/**
 * Retourne la couleur representant au mieux le caractere de la case passee en parametre.
 * @param x, l'abscisse de la case qu'on convertit.
 * @param y, l'ordonnee de la case qu'on convertit.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 * @param symbole, le symbole prealablement retourne par `get_case_char`.
 * @param couleur_background, la couleur prealablement retournee par `get_case_background_color`.
 * @return La couleur representant au mieux le caractere de la case passee en parametre.
 */
int get_case_char_color(int x, int y, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, char* symbole,
                        int couleur_background);


#endif // TANKWAR_GRILLE_H
