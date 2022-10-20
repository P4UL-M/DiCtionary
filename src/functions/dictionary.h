#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../types/nouns.h"

#define NB_LINES 287976
#define MAX_SIZE_LINE 256
#define NOUN_REGEX "\\(.*\\)\t\\(.*\\)\tNom:\\(.*\\)\n"

void extractFile(char *path, p_tree_noun tree);

#endif