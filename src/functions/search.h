/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>
#include "../types/struct.h"

p_node search(p_tree, wchar_t *);
p_form getForm(t_word, wchar_t *);
p_word getWord(p_tree, wchar_t *, bool);
p_form getFormByIndex(t_node, int);

#endif