#ifndef RANDOM_H
#define RANDOM_H
#include <stdbool.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../library/pcg_basic.h"

p_form according(p_tree, int);
int buildPonderation(p_node);
p_word getRandomWord(p_tree, int);
pcg32_random_t seed;

#endif