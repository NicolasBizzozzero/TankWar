#ifndef TANKWAR_AFFICHAGE_H
#define TANKWAR_AFFICHAGE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <tchar.h>
#include "../common/couleurs.h"
#include "../common/string.h"
#include "tank.h"
#include "grille.h"

#define LARGEUR_SEPARATION 58
#define KEY_ARROW_UP 72
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_EXIT 59
#define KEY_ENTER '\r'


/**
 * Change le titre de la fenetre.
 * Cette fonction a ete programmee pour fonctionner avec Windows 10 64 bits. Elle n'a pa ete testee sur d'autres
 * systemes d'exploitations, et il est peu probable qu'elle fonctionne dessus.
 * @param titre, le titre que l'on souhaite attribuer a la fenetre.
 */
void set_titre_fenetre(char* titre);


/**
 * Demande a l'utilisateur d'appuyer sur une touche pour continuer, puis attends un input.
 * Cette fonction a ete programmee pour fonctionner avec Windows 10 64 bits. Elle n'a pa ete testee sur d'autres
 * systemes d'exploitations, et il est peu probable qu'elle fonctionne dessus.
 */
void appuyez_sur_une_touche_pour_continuer(void);


/**
 * Nettoie l'ecran du terminal et replace le curseur a la position (1, 1) (le coin en haut a gauche).
 * Cette fonction a ete programmee pour fonctionner avec Windows 10 64 bits. Elle n'a pa ete testee sur d'autres
 * systemes d'exploitations, et il est peu probable qu'elle fonctionne dessus.
 */
void clear_screen(void);


/**
 * Affiche l'ecran principal du jeu.
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 * @param joueur_actuel, le joueur devant actuellement jouer.
 */
void print_ecran_principal(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                           enum Camp joueur_actuel);


/**
 * Affiche les scores des deux equies
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 */
void print_scores(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu);


/**
 * Affiche l'ecran de selection du tank.
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 * @param joueur_actuel, le joueur devant actuellement jouer.
 * @param tanks, le tableau des tanks du joueur actuel.
 */
void print_selection_tank(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                          enum Camp joueur_actuel, Tank** tanks);


/**
 * Affiche l'ecran de selection de la direction.
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 * @param joueur_actuel, le joueur devant actuellement jouer.
 * @param tanks, le tableau des tanks du joueur actuel.
 * @param direction, la direction actuellement selectionnee.
 */
void print_selection_direction(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                               enum Camp joueur_actuel, Tank** tanks, enum Direction direction);


/**
 * Affiche l'ecran de selection de la direction.
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 * @param joueur_actuel, le joueur devant actuellement jouer.
 * @param tanks, le tableau des tanks du joueur actuel.
 * @param tank, le tank choisi par le joueur actuel.
 * @param direction, la direction actuellement selectionnee.
 * @param profondeur, la profondeur actuellement selectionnee.
 * @param profondeur_max, la profondeur maximale atteignable par le tank.
 */
void print_selection_profondeur(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu,
                                enum Camp joueur_actuel, Tank** tanks, Tank* tank, enum Direction direction,
                                int profondeur, int profondeur_max);


/**
 * Affiche une ligne de separation.
 * Utilisee entre plusieurs composants d'un menu.
 * Est parametree par la macro `LARGEUR_SEPARATION`.
 */
void print_separation(void);


/**
 * Affiche les tanks du joueur jouant actuellement.
 * @param tanks, le tableau des tanks du joueur jouant actuellement.
 */
void print_tanks(Tank** tanks);


/**
 * Affiche une representation graphique d'une grille
 * @param grille, la grille a afficher.
 * @param tanks_camp_vert, le tableau de tanks du camp vert.
 * @param tanks_camp_bleu, le tableau de tanks du camp bleu.
 */
void print_grille(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu);


/**
 * Affiche une representation graphique d'une selection de direction
 * @param direction, la direction actuellement selectionne
 */
void print_direction(enum Direction direction);


/**
 * Affiche une representation graphique d'une selection de profondeur
 * @param profondeur, la profondeur actuellement selectionne
 * @param profondeur_max, la profondeur maximale atteignable par le tank dont on souhaite afficher la profondeur.
 */
void print_profondeur(int profondeur, int profondeur_max);


/**
 * Selectionne le tank qui va jouer en attendant une touche de l'utilisateur.
 * Si l'utilisateur appuie sur une touche flechee, modifie le tank selectionne et retourne `NULL`.
 * Si l'utilisateur appuie sur entree, retourne un pointeur sur le tank actuellement selectionne.
 * Si l'utilisateur appuie sur autre chose, ne fait rien et retourne `NULL`.
 * @param grille, la grille du jeu.
 * @param tanks, le tableau des tanks du joueur actuel.
 * @return Un pointeur sur le tank selectionne, ou `NULL`.
 */
Tank* selection_tank(enum TypeCase** grille, Tank** tanks);


/**
 * Selectionne la direction dans laquelle le tank selectionne va avancer.
 * Si l'utilisateur appuie sur une touche flechee, modifie la selection et retourne `FALSE`.
 * Si l'utilisateur appuie sur entree, retourne `TRUE`.
 * Si l'utilisateur appuie sur autre chose, ne fait rien et retourne `FALSE`.
 * @param direction, la direction actuellement selectionnee.
 * @return Un boolean valant TRUE=1 si la direction est validee, FALSE=0 sinon.
 */
 int selection_direction(enum Direction* direction);


/**
 * Selectionne la profondeur a laquelle le tank selectionne va avancer.
 * Si l'utilisateur appuie sur une touche flechee, modifie la profondeur et retourne `FALSE`.
 * Si l'utilisateur appuie sur entree, retourne `TRUE`.
 * Si l'utilisateur appuie sur autre chose, ne fait rien et retourne `FALSE`.
 * @param profondeur, la profondeur actuellement selectionnee.
 * @param profondeur_max, la profondeur maximale atteignable par le tank.
 * @return Un boolean valant TRUE=1 si la direction est validee, FALSE=0 sinon.
 */
int selection_profondeur(int* profondeur, int profondeur_max);


#endif // TANKWAR_AFFICHAGE_H
