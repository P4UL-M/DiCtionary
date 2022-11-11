#ifndef SENTENCE_H
#define SENTENCE_H

#include <stdbool.h>
#include "../types/struct.h"
#include "../functions/dictionary.h"
#include "../types/struct.h"

void generateSentence(t_dictionary, int, bool);
p_form accords(p_word, unsigned int);

#endif