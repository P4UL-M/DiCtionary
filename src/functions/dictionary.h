/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

#define NB_LINES 287977
#define MAX_SIZE_LINE 256

typedef struct dictionary
{
    p_tree_noun nouns;
    p_tree_adj adjectives;
    p_tree_adv adverbs;
    p_tree_verb verbs;
} t_dictionary, *p_dictionary;

void extractFile(char *path, p_tree_noun tree);

#endif