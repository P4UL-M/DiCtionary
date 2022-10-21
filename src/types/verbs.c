/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the verbs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "verbs.h"

p_tree_verb create_tree_verb()
{
    p_tree_verb tree = malloc(sizeof(t_tree_verb));
    tree->children = malloc(sizeof(p_node_verb) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        tree->children[i] = NULL;
    }
    tree->nb_children = 0;
    return tree;
}

p_node_verb create_node_verb(char val)
{
    p_node_verb node = malloc(sizeof(t_node_verb));
    node->value = val;
    node->children = malloc(sizeof(p_node_verb) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        node->children[i] = NULL;
    }
    node->nb_children = 0;
    node->conjugaisons = malloc(sizeof(t_conjugaison) * MAX_CONJUG);
    node->nb_conjugaisons = 0;
    return node;
}

t_conjugaison create_conjugaison(t_personne pers, t_temps temps, char *word)
{
    t_conjugaison conjugaison = {
        .personne = pers,
        .temps = temps,
        .word = word};
    return conjugaison;
}

bool add_child_verb(p_node_verb parent, p_node_verb child)
{
    if (parent->nb_children < MAX)
    {
        parent->children[parent->nb_children] = child;
        parent->nb_children++;
        return 1;
    }
    return 0;
}

bool add_conjugaison(p_node_verb node, t_conjugaison conjugaison)
{
    if (node->nb_conjugaisons < MAX_CONJUG)
    {
        node->conjugaisons[node->nb_conjugaisons] = conjugaison;
        node->nb_conjugaisons++;
        return 1;
    }
    return 0;
}