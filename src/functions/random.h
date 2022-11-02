#ifndef RANDOM_H
#define RANDOM_H
#include "../types/struct.h"
#include "../types/constants.h"

p_node randomNextLetter(p_child);
p_node findRandom(p_tree);
p_form according(p_tree, int);
int buildPonderation(p_node);
p_node trueRandom(p_tree);

#endif