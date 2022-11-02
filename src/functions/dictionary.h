/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../types/struct.h"
#include "../types/constants.h"

#define NB_LINES 287977
#define MAX_SIZE_LINE 256

typedef struct dictionary
{
    p_tree nouns;
    p_tree adjectives;
    p_tree adverbs;
    p_tree verbs;
} t_dictionary, *p_dictionary;

t_dictionary extractFile(char *path);
char **extractWord(char *source);

#endif