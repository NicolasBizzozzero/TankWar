#ifndef TANKWAR_COULEURS_H
#define TANKWAR_COULEURS_H

#include <windows.h>
#include <stdio.h>
#define FOREGROUND_NOIR 0
#define FOREGROUND_BLEU_FONCE 1
#define FOREGROUND_VERT_FONCE 2
#define FOREGROUND_TURQUOISE 3
#define FOREGROUND_ROUGE_FONCE 4
#define FOREGROUND_VIOLET 5
#define FOREGROUND_VERT_CACA_DOIE 6
#define FOREGROUND_GRIS_CLAIR 7
#define FOREGROUND_GRIS_FONCE 8
#define FOREGROUND_BLEU_FLUO 9
#define FOREGROUND_VERT_FLUO 10
#define FOREGROUND_TURQUOISE_2 11
#define FOREGROUND_ROUGE_FLUO 12
#define FOREGROUND_VIOLET_2 13
#define FOREGROUND_JAUNE 14
#define FOREGROUND_BLANC 15
#define BACKGROUND_NOIR 0
#define BACKGROUND_BLEU 16
#define BACKGROUND_VERT 32
#define BACKGROUND_ROUGE 64
#define BACKGROUND_ROSE BACKGROUND_BLEU | BACKGROUND_ROUGE
#define BACKGROUND_CYAN BACKGROUND_BLEU | BACKGROUND_VERT
#define BACKGROUND_JAUNE BACKGROUND_VERT | BACKGROUND_ROUGE
#define BACKGROUND_BLANC BACKGROUND_BLEU | BACKGROUND_VERT | BACKGROUND_ROUGE

#define DEFAULT_BACKGROUND BACKGROUND_NOIR
#define DEFAULT_FOREGROUND FOREGROUND_BLANC

#define COMMON_LVB_UNDERSCORE 0x8000


/**
 * Definit la couleur du texte et du background du terminal.
 * @param couleur_texte, la couleur du texte desiree.
 * @param couleur_background, la couleur du background desiree.
 */
void set_couleur_terminal(int couleur_texte, int couleur_background);


/**
 * Affiche un texte selon une couleur de foreground et background precise.
 * Reaffecte le background et le foreground aux couleurs par defaut apres affichage. Ces couleurs par defaut sont
 * donnees par les macros `DEFAULT_BACKGROUND` et `DEFAULT_FOREGROUND`.
 * @param texte, le texte que l'on souhaite afficher
 * @param couleur_texte, la couleur du texte que l'on souhaite afficher;
 * @param couleur_background, la couleur du background sur lequel on souhaite afficher le texte.
 */
void print_couleur(char* texte, int couleur_texte, int couleur_background);


/**
 * Affiche un texte en le soulignant.
 * @param texte, le texte a afficher dans l'etat souligne.
 */
void print_texte_souligne(char* texte);


#endif // TANKWAR_COULEURS_H
