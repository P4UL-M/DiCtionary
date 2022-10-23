/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

p_node_noun searchNoun(p_tree_noun, char *);
p_node_verb searchVerb(p_tree_verb, char *);
p_node_adj searchAdj(p_tree_adj, char *);
p_node_adv searchAdv(p_tree_adv, char *);

/*p_node_noun randomNoun(p_tree_noun);
p_node_verb randomVerb(p_tree_verb);
p_node_adj randomAdj(p_tree_adj);
p_node_adv randomAdv(p_tree_adv);*/
#endif