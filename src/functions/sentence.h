#ifndef SENTENCE_H
#define SENTENCE_H

#include <stdbool.h>
#include "../types/struct.h"
#include "../functions/dictionary.h"
#include "../types/struct.h"

void generateSentence(int, t_dictionary);
p_form according(p_tree, int);

#endif