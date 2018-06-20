#include "couleurs.h"


void set_couleur_terminal(int couleur_texte, int couleur_background)
{
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, couleur_texte | couleur_background);
}


void print_couleur(char* texte, int couleur_texte, int couleur_background)
{
    set_couleur_terminal(couleur_texte, couleur_background);
    printf(texte);
    set_couleur_terminal(DEFAULT_FOREGROUND, DEFAULT_BACKGROUND);
}


void print_texte_souligne(char* texte)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // On recupere l'ancien format du texte
    CONSOLE_SCREEN_BUFFER_INFO vieux_attributs;
    GetConsoleScreenBufferInfo(handle, &vieux_attributs);

    // On definit le nouveau format du texte en ajoutant l'attribut "souligne" a TRUE
    SetConsoleTextAttribute(handle, vieux_attributs.wAttributes | COMMON_LVB_UNDERSCORE);

    // On affiche le texte souligne
    printf(texte);

    // On remet le format du texte comme il etait avant
    SetConsoleTextAttribute(handle, vieux_attributs.wAttributes);
}
