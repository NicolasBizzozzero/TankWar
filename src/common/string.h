#ifndef TANKWAR_STRING_H
#define TANKWAR_STRING_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Take a string and repeat it some number of times.
 * Source : https://rosettacode.org/wiki/Repeat_a_string#C
 * @param string, La chaine de caractere a repeter.
 * @param n, Le nombre de repetitions.
 * @return Une chaine de caracteres composee de `n` repetitions de `string`.
 */
char* string_repeat(const char* string, int n);

#endif // TANKWAR_STRING_H
