#ifndef TANKWAR_TANK_H
#define TANKWAR_TANK_H


#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <tchar.h>
#include "../common/boolean.h"
#include "case.h"
#define NOMBRE_TANKS_INITIAUX 14
#define CHAR_TANK_COMMANDANT "C"
#define CHAR_TANK_SOLDAT "S"


enum TypeTank {SOLDAT, COMMANDANT};
enum Camp {VERT, BLEU};
enum Direction {NORD, EST, SUD, OUEST};


typedef struct Tank {
    enum TypeTank type_tank;           // Le type du tank (commandant ou simple soldat)
    enum Camp camp;                    // Le camp auquel le tank appartient (Vert ou bleu)
    int x, y;                          // La position du tank sur la grille. Si le tank est mort, sa position devrait etre a -1.
    int est_mort;                      // Boolean valant 0 si le tank est mort, 1 s'il est vivant.
    int est_dans_le_camp_adverse;      // Boolean valant 1 si le tank est dans le camp ennemi, 0 sinon.
    int est_actuellement_selectionne;  // Boolean valant 1 si le tank est actuellement selectionne par le joueur, 0 sinon.
} Tank;


/**
 * Initialise un tank puis le retourne.
 * @param type_tank, le type du tank a initialiser.
 * @param camp, le camp du tank a initialiser.
 * @param x, la position en abscisse du tank sur la grille.
 * @param y, la position en ordonnee du tank sur la grille.
 * @param est_mort, un boolean representant le fait que le tank est mort.
 * @param est_dans_le_camp_adverse, un boolean representant le fait que le tank soit dans le camp adverse.
 * @param est_actuellement_selectionne, un boolean representant le fait que le tank est actuellement selectionne par le
 * joueur.
 * @return Le tank initialise.
 */
Tank* init_tank(enum TypeTank type_tank, enum Camp camp, int x, int y, int est_mort, int est_dans_le_camp_adverse,
                int est_actuellement_selectionne);


/**
 * Initialise un tableau de tanks du camp bleu.
 * @return Le tableau de tous les tanks appartenant au camp bleu.
 */
Tank** init_tanks_camp_bleu(void);


/**
 * Initialise un tableau de tanks du camp vert.
 * @return Le tableau de tous les tanks appartenant au camp vert.
 */
Tank** init_tanks_camp_vert(void);


/**
 * Retourne un boolean correspondant au fait que le tank se trouve sur la case de coordonnees (x, y).
 * @param tank, le tank dont on souhaite verifier les coordonnees.
 * @param x, l'abscisse de la case a verifier.
 * @param y, l'ordonnee de la case a verifier.
 * @return Un entier a 0 pour FALSE, et 1 pour TRUE.
 */
int tank_est_sur_la_case(Tank* tank, int x, int y);


/**
 * Retourne parmi le tableau de Tank `tanks`, le pointeur sur le tank se trouvant a la position (x, y).
 * Retourne `NULL` si ce tank n'est pas present dans le tableau.
 * @param tanks, le tableau contenant les tanks dont l'on souhaite verifier la position.
 * @param x, l'abscisse que l'on souhaite verifier.
 * @param y, l'ordonnee que l'on souhaite verifier.
 * @return Un pointeur sur le tank dont la position est egale a (x, y). Le pointeur `NULL` si aucun tank n'a ete trouve.
 */
Tank* get_tank_by_position(Tank** tanks, int x, int y);


/**
 * Retourne parmi les tableaux de Tank , le pointeur sur le tank se trouvant a la position (x, y).
 * Retourne `NULL` si ce tank n'est pas present dans le tableau.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param x, l'abscisse que l'on souhaite verifier.
 * @param y, l'ordonnee que l'on souhaite verifier.
 * @return Un pointeur sur le tank dont la position est egale a (x, y). Le pointeur `NULL` si aucun tank n'a ete trouve.
 */
Tank* get_all_tank_by_position( Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y);


/**
 * Retourne parmi le tableau de Tank `tanks`, le pointeur sur le premier tank encore en vie.
 * Retourne `NULL` si ce tank n'est pas present dans le tableau.
 * @param tanks, le tableau contenant les tanks dont l'on souhaite verifier la position.
 * @return Un pointeur sur le premier tank encore en vie.
 */
Tank* get_first_tank_alive(Tank** tanks);


/**
 * Recupere le premier tank actuellement en vie et le designe en tant que tank actuellement selectionne. Ne fait rien si
 * aucun tank n'est en vie.
 * Cette fonction est utilisee une et une seule fois au debut de chaque tour.
 * @param tanks, le tableau de tanks.
 */
void set_first_tank_alive_as_currently_selectionned(Tank** tanks);


/**
 * Retourne l'index du tank qu'on selectionne actuellement. Retourne `NULL` si aucun n'est selectionne.
 * @param tanks, le tableau de tanks.
 * @return l'index du seul tank actuellement selectionne. Retourne `NULL` si aucun n'est selectionne.
 */
int get_index_tank_actuellement_selectionne(Tank** tanks);


/**
 * Retourne une valeur representant qu'un tank a le droit de se trouver sur une case de coordonnees (x, y) (sans prendre
 * en compte le fait qu'il ne puisse l'atteindre).
 * @param case_actuelle, le type de la case dont l'on souhaite verifier l'accessibilite.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param tank, le tank dont on souhaite savoir s'il peut atteindre la case.
 * @param x, l'abscisse de la case dont on souhaite savoir si on peut l'atteindre.
 * @param y, l'ordonnee de la case dont on souhaite savoir si on peut l'atteindre.
 * @return une valeur representant qu'un tank a le droit de se trouver sur une case de coordonnees (x, y). Si TRUE=1,
 * alors le tank peut l'atteindre. Si FALSE=0, alors le tank ne peut pas l'atteindre. Si -1, alors le tank peut
 * l'atteindre mais doit s'y arreter.
 */
int tank_peut_se_trouver_ici(enum TypeCase case_actuelle, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, Tank* tank, int x,
                             int y);


/**
 * Retourne un boolean representant le fait qu'un tank se trouve a cette case.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param x, l'abscisse de la case dont on souhaite savoir si un tank se trouve ici.
 * @param y, l'ordonnee de la case dont on souhaite savoir si un tank se trouve ici.
 * @return un boolean representant le fait qu'un tank se trouve a cette case.
 */
int il_y_a_un_tank_ici(Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y);


/**
 * Retourne un boolean representant le fait qu'un tank allie se trouve a cette case.
 * @param tank, le tank dont on souhaite comparer l'autre tank.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param x, l'abscisse de la case dont on souhaite savoir si un tank allie se trouve ici.
 * @param y, l'ordonnee de la case dont on souhaite savoir si un tank allie se trouve ici.
 * @return un boolean representant le fait qu'un tank allie se trouve a cette case.
 */
int il_y_a_un_tank_allie_ici(Tank* tank, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y);


/**
 * Retourne un boolean representant le fait qu'un tank ennemi se trouve a cette case.
 * @param tank, le tank dont on souhaite comparer l'autre tank.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param x, l'abscisse de la case dont on souhaite savoir si un tank ennemi se trouve ici.
 * @param y, l'ordonnee de la case dont on souhaite savoir si un tank ennemi se trouve ici.
 * @return un boolean representant le fait qu'un tank ennemi se trouve a cette case.
 */
int il_y_a_un_tank_ennemi_ici(Tank* tank, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y);


/**
 * Retourne la profondeur maximale que peut atteindre un tank sur une grille selon une direction.
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param tank, le tank dont on souhaite calculer la profondeur max
 * @param direction, la direction dont on souhaite calculer la profondeur max
 * @return La profondeur maximale atteignable par un tank selon une direction sur la grille.
 */
int get_profondeur_max(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, Tank* tank, enum Direction direction);


/**
 * Retourne un boolean correspondant au fait que le tank soit coince et ne puisse plus avancer.
 * @param grille, la grille du jeu.
 * @param tanks_camp_vert, le tableau des tanks du camp vert.
 * @param tanks_camp_bleu, le tableau des tanks du camp bleu.
 * @param tank, le tank dont on verifie l'etat.
 * @return Un boolean a TRUE=1 si le tank est coince, FALSE=0 sinon.
 */
int tank_coince(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, Tank* tank);


/**
 * Retourne un boolean valant TRUE=1 si aucun tank n'est encore en vie, FALSE=0 sinon.
 * @param tanks, l'equipe de tanks dont on souhaite verifier la vitalité.
 * @return un boolean valant TRUE=1 si aucun tank n'est encore en vie, FALSE=0 sinon.
 */
int equipe_decimee(Tank** tanks);


/**
 * Affiche un caractere correspondant au tank.
 * @param tank, le tank que l'on souhaite representer.
 * @return Le caractere representant le mieux le tank.
 */
char* tank_to_str(Tank* tank);


/**
 * Retourne une chaine de caractere representant le camp passe en parametre
 * @param camp, le camp qu'on souhaite convertir en string.
 * @return Une chaine de caractere correspondant au camp passe en parametrre
 */
char* camp_to_str(enum Camp camp);


/**
 * Retourne la direction a gauche de la direction passee en parametre.
 * @param direction, la direction actuelle.
 * @return la direction a gauche de la direction passee en parametre.
 */
enum Direction get_direction_gauche(enum Direction direction);


/**
 * Retourne la direction a droite de la direction passee en parametre.
 * @param direction, la direction actuelle.
 * @return la direction a droite de la direction passee en parametre.
 */
enum Direction get_direction_droite(enum Direction direction);


/**
 * Retourne une chaine de caracteres representant une direction.
 * @param direction, la direction que l'on souhaite representer.
 * @return la chaine de caracteres representant la direction.
 */
char* direction_to_str(enum Direction direction);


/**
 * Retourne le camp adversaire du camp passe en parametre.
 * @param camp, le camp dont on souhaite obtenir le camp adverse.
 * @return le camp adversaire du camp passe en parametre.
 */
enum Camp camp_adverse(enum Camp camp);


/**
 * Deplace un tank sur une nouvelle case.
 * @param grille, la grille du jeu.
 * @param tanks_adverses, le tableau des tanks adverses.
 * @param tank, le tank qu'on deplace
 * @param direction, la direction dans laquelle on deplace le tank.
 * @param profondeur, la profondeur a laquelle on se deplace.
 */
void deplace_tank(enum TypeCase** grille, Tank** tanks_adverses, Tank* tank, enum Direction direction, int profondeur);


/**
 * Calcule le score d'une equipe.
 * @param camp, le camp dont on calcule le score.
 * @param grille, la grille du jeu.
 * @param tanks, le tableau des tanks de l'equipe dont on calcule le score.
 * @return Le score qu'obtient l'equipe passe en parametre.
 */
int get_score_equipe(enum Camp camp, enum TypeCase** grille, Tank** tanks);


/**
 * Calcule le score d'un tank.
 * @param camp, le camp dont on calcule le score.
 * @param grille, la grille du jeu.
 * @param tanks, le  tank dont on calcule le score.
 * @return Le score qu'obtient le tank passe en parametre.
 */
int get_score_tank(enum Camp camp, enum TypeCase** grille, Tank* tank);


/**
 * Retourne un boolean representant le fait que `tank` soit un commandant et qu'il se situe sur la case du commandant
 * adverse.
 * @param tank, le tank dont on souhaite savoir s'il est un commandant et qu'il se situe sur la case du commandant
 * adverse.
 * @return un boolean representant le fait que `tank` soit un commandant et qu'il se situe sur la case du commandant
 * adverse.
 */
int est_sur_la_case_du_commandant_adverse(Tank* tank);


#endif // TANKWAR_TANK_H
