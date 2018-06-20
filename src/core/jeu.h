#ifndef TANKWAR_JEU_H
#define TANKWAR_JEU_H


#include <windows.h>
#include <unistd.h>
#include "../common/aleatoire.h"
#include "../common/boolean.h"
#include "../common/couleurs.h"
#include "grille.h"
#include "tank.h"
#include "affichage.h"


/**
 * Tire au hasard le premier camp a jouer, affiche les messages d'informations necessaires pour le joueur, puis attends
 * une entree apres que tout soit fini.
 * @return Le joueur tire au hasard, celui qui va jouer le premier.
 */
enum Camp tirage_au_sort_premier_joueur(void);


/**
 * Verifie si la partie est terminee ou non.
 * @param grille, la grille de jeu.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @return un boolean a TRUE=1 si le jeu est termine, ou a FALSE=0 sinon.
 */
int jeu_fini(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu);


#endif // TANKWAR_JEU_H
