#include "jeu.h"


int jeu_fini(enum TypeCase** grille, Tank** tanks_camp_vert, Tank** tanks_camp_bleu)
{
    int i;
    int tanks_verts_vivants, tanks_verts_dans_la_base_ennemie = 0;
    int tanks_bleus_vivants, tanks_bleus_dans_la_base_ennemie = 0;
    for (i=0; i < NOMBRE_TANKS_INITIAUX; i++) {
        // On comptabilise les tanks du camp vert
        if (tanks_camp_vert[i]->est_mort == FALSE) {
            tanks_verts_vivants++;
            if (tanks_camp_vert[i]->est_dans_le_camp_adverse == TRUE) {
                tanks_verts_dans_la_base_ennemie++;
            }
        }

        // On comptabilise les tanks du camp bleu
        if (tanks_camp_bleu[i]->est_mort == FALSE) {
            tanks_bleus_vivants++;
            if (tanks_camp_bleu[i]->est_dans_le_camp_adverse == TRUE) {
                tanks_bleus_dans_la_base_ennemie++;
            }
        }
    }

    // Si tous les tanks d'un camp sont morts, on ne souhaite pas renvoyer TRUE quand meme. Il faut attendre que les
    // tanks de l'autre camps soient tous dans la base ennemie.
    if ((tanks_bleus_vivants == 0) && (tanks_verts_vivants != tanks_verts_dans_la_base_ennemie)) {
        return FALSE;
    } else if ((tanks_verts_vivants == 0) && (tanks_bleus_vivants != tanks_bleus_dans_la_base_ennemie)) {
        return FALSE;
    }

    // Sinon on verifie que tous les tanks vivants sont dans la base ennemie
    else if (tanks_verts_vivants == tanks_verts_dans_la_base_ennemie) {
        return TRUE;
    } else if (tanks_bleus_vivants == tanks_bleus_dans_la_base_ennemie) {
        return TRUE;
    } else {
        return FALSE;
    }
}


enum Camp tirage_au_sort_premier_joueur(void)
{
    printf("Tirage au sort du camp qui commence ...\n");
    enum Camp premier_joueur;
    sleep(1);  // Simulation d'un tirage au sort
    if (get_int_aleatoirement(0, 2) == 0) {
        premier_joueur = VERT;
        printf("Le camp VERT commence.\n");
    } else {
        premier_joueur = BLEU;
        printf("Le camp BLEU commence.\n");
    }

    appuyez_sur_une_touche_pour_continuer();

    return premier_joueur;
}
