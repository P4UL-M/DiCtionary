/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef SEARCH_H
#define SEARCH_H

#include "../types/struct.h"

p_node search(p_tree, char *);
p_form getForm(p_word, char *);
p_word getWord(p_tree, char *);

#endif