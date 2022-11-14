/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains all random functions*/
#ifndef RANDOM_H
#define RANDOM_H
#include <stdbool.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/dictionary.h"

void buildPonderations(t_dictionary);
p_word getRandomWord(p_tree, bool);

#endif