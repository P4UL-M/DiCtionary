/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>
#include "../types/struct.h"
#include "../types/pile.h"

p_node search(p_tree, char *);
p_form getForm(t_word, char *);
p_word getWord(p_tree, char *, bool);
p_form getFormByIndex(t_node, int);
void autocompletion(p_tree, char *, p_fpile);
p_fpile depileCompletion(p_pile, p_fpile, p_node, char *, int);

#endif