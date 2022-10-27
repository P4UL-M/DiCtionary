/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef SEARCH_H
#define SEARCH_H

#include "../types/struct.h"

p_node search(p_tree, char *);
p_node randomNextLetter(p_child);
p_node findRandom(p_tree);
p_form according(p_node, int);
p_form getForm(p_node, char *);

#endif