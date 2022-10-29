#ifndef RANDOM_H
#define RANDOM_H
#include "../types/struct.h"
#include "../types/constants.h"
#include "../types/intTree.h"

p_node randomNextLetter(p_child);
p_node findRandom(p_tree);
p_form according(p_tree, int);
p_itree createPonderationTree(p_tree dico);
p_node trueRandom(p_tree dico, p_itree ponderationTree);

#endif