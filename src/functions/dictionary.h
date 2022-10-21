/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../types/nouns.h"

#define NB_LINES 287977
#define MAX_SIZE_LINE 256

void extractFile(char *path, p_tree_noun tree);

#endif