#ifndef RANDOM_H
#define RANDOM_H
#include <stdbool.h>
#include "../types/struct.h"
#include "../types/constants.h"

p_form according(p_tree, int);
int buildPonderation(p_node);
p_word getRandomWord(p_tree, bool);

#endif