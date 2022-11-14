/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains all searching functions*/
#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>
#include "../types/struct.h"
#include "../types/pile.h"

p_node search(p_tree, wchar_t *);
p_form getForm(t_word, wchar_t *);
p_word getWord(p_tree, wchar_t *, bool);
p_form getFormByIndex(t_node, int);
void autocompletion(p_tree, wchar_t *, p_fpile);

#endif