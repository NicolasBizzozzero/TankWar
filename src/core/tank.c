#include "tank.h"


Tank* init_tank(enum TypeTank type_tank, enum Camp camp, int x, int y, int est_mort, int est_dans_le_camp_adverse,
                int est_actuellement_selectionne)
{
    // On alloue l'espace memoire necessaire pour obtenir un tank
    Tank* tank = (Tank*) malloc(sizeof(enum TypeTank) + sizeof(enum Camp) + (sizeof(int) * 2) + sizeof(int) +
                                sizeof(int) + sizeof(int));

    // On initialise le tank
    tank->type_tank = type_tank;
    tank->camp = camp;
    tank->x = x;
    tank->y = y;
    tank->est_mort = est_mort;
    tank->est_dans_le_camp_adverse = est_dans_le_camp_adverse;
    tank->est_actuellement_selectionne = est_actuellement_selectionne;

    return tank;
}


Tank** init_tanks_camp_vert(void)
{
    // On alloue l'espace memoire necessaire pour un tableau de `NOMBRE_TANKS_INITIAUX` pointeurs sur Tank.
    Tank** tanks = (Tank**) malloc(sizeof(Tank*) * NOMBRE_TANKS_INITIAUX);

    tanks[0] = init_tank(COMMANDANT, VERT, 0, 0, FALSE, FALSE, FALSE);
    tanks[1] = init_tank(SOLDAT, VERT, 1, 0, FALSE, FALSE, FALSE);
    tanks[2] = init_tank(SOLDAT, VERT, 2, 0, FALSE, FALSE, FALSE);
    tanks[3] = init_tank(SOLDAT, VERT, 3, 0, FALSE, FALSE, FALSE);
    tanks[4] = init_tank(SOLDAT, VERT, 4, 0, FALSE, FALSE, FALSE);
    tanks[5] = init_tank(SOLDAT, VERT, 0, 1, FALSE, FALSE, FALSE);
    tanks[6] = init_tank(SOLDAT, VERT, 2, 1, FALSE, FALSE, FALSE);
    tanks[7] = init_tank(SOLDAT, VERT, 3, 1, FALSE, FALSE, FALSE);
    tanks[8] = init_tank(SOLDAT, VERT, 0, 2, FALSE, FALSE, FALSE);
    tanks[9] = init_tank(SOLDAT, VERT, 1, 2, FALSE, FALSE, FALSE);
    tanks[10] = init_tank(SOLDAT, VERT, 2, 2, FALSE, FALSE, FALSE);
    tanks[11] = init_tank(SOLDAT, VERT, 0, 3, FALSE, FALSE, FALSE);
    tanks[12] = init_tank(SOLDAT, VERT, 1, 3, FALSE, FALSE, FALSE);
    tanks[13] = init_tank(SOLDAT, VERT, 0, 4, FALSE, FALSE, FALSE);

    return tanks;
}


Tank** init_tanks_camp_bleu(void)
{
    // On alloue l'espace memoire necessaire pour un tableau de `NOMBRE_TANKS_INITIAUX` pointeurs sur Tank.
    Tank** tanks = (Tank**) malloc(sizeof(Tank*) * NOMBRE_TANKS_INITIAUX);

    tanks[0] = init_tank(COMMANDANT, BLEU, 10, 10, FALSE, FALSE, FALSE);
    tanks[1] = init_tank(SOLDAT, BLEU, 9, 10, FALSE, FALSE, FALSE);
    tanks[2] = init_tank(SOLDAT, BLEU, 8, 10, FALSE, FALSE, FALSE);
    tanks[3] = init_tank(SOLDAT, BLEU, 7, 10, FALSE, FALSE, FALSE);
    tanks[4] = init_tank(SOLDAT, BLEU, 6, 10, FALSE, FALSE, FALSE);
    tanks[5] = init_tank(SOLDAT, BLEU, 10, 9, FALSE, FALSE, FALSE);
    tanks[6] = init_tank(SOLDAT, BLEU, 8, 9, FALSE, FALSE, FALSE);
    tanks[7] = init_tank(SOLDAT, BLEU, 7, 9, FALSE, FALSE, FALSE);
    tanks[8] = init_tank(SOLDAT, BLEU, 10, 8, FALSE, FALSE, FALSE);
    tanks[9] = init_tank(SOLDAT, BLEU, 9, 8, FALSE, FALSE, FALSE);
    tanks[10] = init_tank(SOLDAT, BLEU, 8, 8, FALSE, FALSE, FALSE);
    tanks[11] = init_tank(SOLDAT, BLEU, 10, 7, FALSE, FALSE, FALSE);
    tanks[12] = init_tank(SOLDAT, BLEU, 9, 7, FALSE, FALSE, FALSE);
    tanks[13] = init_tank(SOLDAT, BLEU, 10, 6, FALSE, FALSE, FALSE);

    return tanks;
}


int tank_est_sur_la_case(Tank* tank, int x, int y)
{
    return ((tank->x == x) && (tank->y == y) ? TRUE : FALSE);
}


Tank* get_tank_by_position(Tank** tanks, int x, int y)
{
    int i;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        if (tank_est_sur_la_case(tanks[i], x, y))
            return tanks[i];
    }
    return NULL;
}

Tank* get_all_tank_by_position(Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y)
{
    int i;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        if (tank_est_sur_la_case(tanks_camp_vert[i], x, y) == TRUE)
            return tanks_camp_vert[i];
        else if (tank_est_sur_la_case(tanks_camp_bleu[i], x, y) == TRUE)
            return tanks_camp_bleu[i];
    }
    return NULL;
}


Tank* get_first_tank_alive(Tank** tanks)
{
    int i;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        if (tanks[i]->est_mort == FALSE)
            return tanks[i];
    }
    return NULL;
}


void set_first_tank_alive_as_currently_selectionned(Tank** tanks)
{
    Tank* tank = get_first_tank_alive(tanks);
    if (tank != NULL)
        tank->est_actuellement_selectionne = TRUE;
}


int get_index_tank_actuellement_selectionne(Tank** tanks)
{
    int i;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        if (tanks[i]->est_actuellement_selectionne == TRUE)
            return i;
    }

    // Ne devrait jamais arriver, il y a toujours un tank selectionne
    exit(EXIT_FAILURE);
}


int tank_peut_se_trouver_ici(enum TypeCase case_actuelle, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, Tank* tank, int x,
                             int y)
{
    int true_mais_il_doit_s_y_arreter = -1;

    switch (case_actuelle) {
        case VIDE:
            // Si un tank est dans un camp adverse, il ne peut le quitter
            if (tank->est_dans_le_camp_adverse)
                return FALSE;

            if (tank->type_tank == COMMANDANT) {
                // Un commandant peut detruire tout type de tank
                if (il_y_a_un_tank_ennemi_ici(tank, tanks_camp_vert, tanks_camp_bleu, x, y) == TRUE)
                    return true_mais_il_doit_s_y_arreter;
                else if (il_y_a_un_tank_allie_ici(tank, tanks_camp_vert, tanks_camp_bleu, x, y) == TRUE)
                    return FALSE;
                else
                    return TRUE;
            } else {
                // Un soldat ne peut detruire que les soldats
                if (il_y_a_un_tank_ennemi_ici(tank, tanks_camp_vert, tanks_camp_bleu, x, y) == TRUE) {
                    Tank *tank_ennemi = get_all_tank_by_position(tanks_camp_vert, tanks_camp_bleu, x, y);
                    if (tank_ennemi->type_tank == COMMANDANT)
                        return FALSE;
                    else
                        return true_mais_il_doit_s_y_arreter;
                } else if (il_y_a_un_tank_allie_ici(tank, tanks_camp_vert, tanks_camp_bleu, x, y) == TRUE)
                    return FALSE;
                else
                    return TRUE;
            }
        case MINE:
            return FALSE;
        case POLLUEE:
            if (tank->type_tank == SOLDAT)
                // Un soldat ne peut pas se trouver sur une case polluee
                return FALSE;
            else {
                // Un commandant ne peut pas capturer un tank sur une case polluee
                if (il_y_a_un_tank_ici(tanks_camp_vert, tanks_camp_bleu, x, y) == TRUE)
                    return FALSE;
                else
                    return TRUE;
            }
        case BASE_VERTE:
            // Aucune difference, nous considerons que la case est vide
            return tank_peut_se_trouver_ici(VIDE, tanks_camp_vert, tanks_camp_bleu, tank, x, y);
        case BASE_BLEUE:
            // Aucune difference, nous considerons que la case est vide
            return tank_peut_se_trouver_ici(VIDE, tanks_camp_vert, tanks_camp_bleu, tank, x, y);
        default:
            // Ne devrait jamais etre atteint
            exit(EXIT_FAILURE);
    }
}


int il_y_a_un_tank_ici(Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y)
{
    return (((get_tank_by_position(tanks_camp_vert, x, y) == NULL) &&
             (get_tank_by_position(tanks_camp_bleu, x, y) == NULL)) ? FALSE : TRUE);
}


int il_y_a_un_tank_allie_ici(Tank* tank, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y)
{
    if (tank->camp == VERT) {
        return (get_tank_by_position(tanks_camp_vert, x, y) == NULL ? FALSE : TRUE);
    } else {
        return (get_tank_by_position(tanks_camp_bleu, x, y) == NULL ? FALSE : TRUE);
    }
}


int il_y_a_un_tank_ennemi_ici(Tank* tank, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, int x, int y)
{
    if (tank->camp == BLEU) {
        return (get_tank_by_position(tanks_camp_vert, x, y) == NULL ? FALSE : TRUE);
    } else {
        return (get_tank_by_position(tanks_camp_bleu, x, y) == NULL ? FALSE : TRUE);
    }
}


int get_profondeur_max(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, Tank* tank, enum Direction direction)
{
    int taille_plateau = 11;

    // On calcule la profondeur maximale en fonction de chaque distance
    int profondeur_max = 0;
    int res;
    int x = 0;
    int y = 0;
    switch (direction) {
        case NORD:
            for (y=(tank->y) - 1; y >= 0; y--) {
                if ((res = tank_peut_se_trouver_ici(grille[y][tank->x], tanks_camp_vert, tanks_camp_bleu, tank, tank->x, y)) == TRUE)
                    profondeur_max++;
                else if (res == -1)
                    return ++profondeur_max;
                else
                    return profondeur_max;
            }
            return profondeur_max;

        case OUEST:
            for (x=(tank->x) - 1; x >= 0; x--) {
                if ((res = tank_peut_se_trouver_ici(grille[tank->y][x], tanks_camp_vert, tanks_camp_bleu, tank, x, tank->y)) == TRUE)
                    profondeur_max++;
                else if (res == -1)
                    return ++profondeur_max;
                else
                    return profondeur_max;
            }
            return profondeur_max;

        case SUD:
            for (y=(tank->y) + 1; y < taille_plateau; y++) {
                if ((res = tank_peut_se_trouver_ici(grille[y][tank->x], tanks_camp_vert, tanks_camp_bleu, tank, tank->x, y)) == TRUE)
                    profondeur_max++;
                else if (res == -1)
                    return ++profondeur_max;
                else
                    return profondeur_max;
            }
            return profondeur_max;

        case EST:
            for (x=(tank->x) + 1; x < taille_plateau; x++) {
                if ((res = tank_peut_se_trouver_ici(grille[tank->y][x], tanks_camp_vert, tanks_camp_bleu, tank, x, tank->y)) == TRUE)
                    profondeur_max++;
                else if (res == -1)
                    return ++profondeur_max;
                else
                    return profondeur_max;
            }
            return profondeur_max;
        default:
            // Ne devrait jamais etre atteint
            exit(EXIT_FAILURE);
    }
}


int tank_coince(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu, Tank* tank)
{
    if (tank == NULL)
        return TRUE;
    return ((get_profondeur_max(grille, tanks_camp_vert, tanks_camp_bleu, tank, NORD) == 0 &&
             get_profondeur_max(grille, tanks_camp_vert, tanks_camp_bleu, tank, EST) == 0 &&
             get_profondeur_max(grille, tanks_camp_vert, tanks_camp_bleu, tank, SUD) == 0 &&
             get_profondeur_max(grille, tanks_camp_vert, tanks_camp_bleu, tank, OUEST) == 0) ? TRUE : FALSE);
}


int equipe_decimee(Tank** tanks)
{
    return (get_first_tank_alive(tanks) == NULL ? TRUE : FALSE);
}


char* tank_to_str(Tank* tank)
{
    return (tank->type_tank == COMMANDANT ? CHAR_TANK_COMMANDANT : CHAR_TANK_SOLDAT);
}


char* camp_to_str(enum Camp camp)
{
    return (camp == VERT ? "VERT" : "BLEU");
}


enum Direction get_direction_droite(enum Direction direction)
{
    switch (direction) {
        case NORD:
            return EST;
        case OUEST:
            return NORD;
        case SUD:
            return OUEST;
        case EST:
            return SUD;
        default:
            // Ne devrait jamais etre atteint
            exit(EXIT_FAILURE);
    }
}


enum Direction get_direction_gauche(enum Direction direction)
{
    switch (direction) {
        case NORD:
            return OUEST;
        case OUEST:
            return SUD;
        case SUD:
            return EST;
        case EST:
            return NORD;
        default:
            // Ne devrait jamais etre atteint
            exit(EXIT_FAILURE);
    }
}


char* direction_to_str(enum Direction direction)
{
    switch (direction) {
        case NORD:
            return "Nord";
        case OUEST:
            return "Ouest";
        case SUD:
            return "Sud";
        case EST:
            return "Est";
        default:
            // Ne devrait jamais etre atteint
            exit(EXIT_FAILURE);
    }
}


enum Camp camp_adverse(enum Camp camp)
{
    return (camp == VERT ? BLEU : VERT);
}


void deplace_tank(enum TypeCase** grille, Tank** tanks_adverses, Tank* tank, enum Direction direction, int profondeur)
{
    // On calcule la nouvelle position
    int x, y;
    switch(direction) {
        case NORD:
            x = tank->x;
            y = (tank->y) - profondeur;
            break;
        case EST:
            x = (tank->x) + profondeur;
            y = tank->y;
            break;
        case SUD:
            x = tank->x;
            y = (tank->y) + profondeur;
            break;
        case OUEST:
            x = (tank->x) - profondeur;
            y = tank->y;
            break;
    }

    // On deplace le tank
    tank->x = x;
    tank->y = y;

    // On verifie si le tank se trouve dans la base ennemie
    if ((tank->est_dans_le_camp_adverse == FALSE) &&
        (((grille[y][x] == BASE_VERTE) && (tank->camp == BLEU)) ||
         ((grille[y][x] == BASE_BLEUE) && (tank->camp == VERT))))
        tank->est_dans_le_camp_adverse = TRUE;

    // On tue l'hypothetique ennemi qui se trouvait sur la case
    Tank* tank_adverse;
    if ((tank_adverse = get_tank_by_position(tanks_adverses, x, y)) != NULL) {
        tank_adverse->est_mort = TRUE;
        tank_adverse->x = -1;
        tank_adverse->y = -1;
    }

    // Une fois que le tank a ete deplace, il n'est donc plus selectionne
    tank->est_actuellement_selectionne = FALSE;
}


int get_score_equipe(enum Camp camp, enum TypeCase** grille, Tank** tanks)
{
    int i;
    int score = 0;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        score += get_score_tank(camp, grille, tanks[i]);
    }
    return score;
}


int get_score_tank(enum Camp camp, enum TypeCase** grille, Tank* tank)
{
    // Si le tank est mort il ne vaut rien
    if (tank->est_mort == TRUE)
        return 0;

    // Si le tank est un commandant sur la case du commandant adverse, il vaut cher
    if (est_sur_la_case_du_commandant_adverse(tank) == TRUE)
        return 3;

    // Si le tank est dans le camp adversaire, il vaut un peu
    if (tank->est_dans_le_camp_adverse == TRUE)
        return 2;

    // Sinon, il vaut pas grand chose mais c'est deja ca
    else
        return 1;
}


int est_sur_la_case_du_commandant_adverse(Tank* tank)
{
    int taille_plateau = 11;

    // Les soldats ne gagnent pas plus de points en etant sur cette case
    if (tank->type_tank == SOLDAT)
        return FALSE;

    if (tank->camp == VERT) {
        return ((tank->x == taille_plateau - 1) && (tank->y == taille_plateau - 1) ? TRUE : FALSE);
    } else {
        return ((tank->x == 0) && (tank->y == 0) ? TRUE : FALSE);
    }
}