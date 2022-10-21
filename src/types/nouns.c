/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the nouns*/
#include "nouns.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Path: src/types/noun.c
p_tree_noun create_tree_noun()
{
    p_tree_noun tree = malloc(sizeof(t_tree_noun));
    tree->children = malloc(sizeof(p_node_noun) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        tree->children[i] = NULL;
    }
    tree->nb_children = 0;
    return tree;
}

p_node_noun create_node_noun(char val)
{
    p_node_noun node = malloc(sizeof(t_node_noun));
    node->value = val;
    node->children = malloc(sizeof(p_node_noun) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        node->children[i] = NULL;
    }
    node->nb_children = 0;
    node->declinaisons = malloc(sizeof(t_declinaison_noun) * MAX_DECL);
    node->nb_declinaisons = 0;
    return node;
}

t_declinaison_noun create_declinaison(t_forme_noun forme, char *word)
{
    t_declinaison_noun declinaison = {
        .forme = forme,
        .word = word,
    };
    return declinaison;
}

bool add_child(p_node_noun parent, p_node_noun child)
{
    if (parent->nb_children < MAX)
    {
        parent->children[parent->nb_children] = child;
        parent->nb_children++;
        return 1;
    }
    return 0;
}

bool add_declinaison(p_node_noun node, t_declinaison_noun declinaison)
{
    if (node->nb_declinaisons < MAX_DECL)
    {
        node->declinaisons[node->nb_declinaisons] = declinaison;
        node->nb_declinaisons++;
        return 1;
    }
    return 0;
}