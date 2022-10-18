#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "verb.h"

p_tree_verbs create_tree_verbs()
{
    p_tree_verbs tree = malloc(sizeof(t_tree_verbs));
    tree->children = malloc(sizeof(p_node_verbs) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        tree->children[i] = NULL;
    }
    tree->nb_children = 0;
    return tree;
}

p_node_verbs create_node_verbs(char val)
{
    p_node_verbs node = malloc(sizeof(t_node_verbs));
    node->value = val;
    node->children = malloc(sizeof(p_node_verbs) * MAX);
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

bool add_child_verbs(p_node_verbs parent, p_node_verbs child)
{
    if (parent->nb_children < MAX)
    {
        parent->children[parent->nb_children] = child;
        parent->nb_children++;
        return 1;
    }
    return 0;
}

bool add_conjugaison(p_node_verbs node, t_conjugaison conjugaison)
{
    if (node->nb_conjugaisons < MAX_CONJUG)
    {
        node->conjugaisons[node->nb_conjugaisons] = conjugaison;
        node->nb_conjugaisons++;
        return 1;
    }
    return 0;
}