#include <stdio.h>
#include <stdlib.h>
#include "verb.h"

p_tree_verbs create_tree_verbs()
{
    p_tree_verbs tree = malloc(sizeof(p_tree_verbs));
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
    p_node_verbs node = malloc(sizeof(p_node_verbs));
    node->val = val;
    node->children = malloc(sizeof(p_node_verbs) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        node->children[i] = NULL;
    }
    node->nb_children = 0;
    node->conjugaisons = malloc(sizeof(p_conjugaison) * 18); // To change if we want to integrate all times
    for (int i = 0; i < 18; i++)
    {
        node->conjugaisons[i] = NULL;
    }
    node->nb_conjugaisons = 0;
    return node;
}

p_conjugaison create_conjugaison(t_personne pers, t_temps temps, char *word)
{
    p_conjugaison conjugaison = malloc(sizeof(conjugaison));
    conjugaison->personne = pers;
    conjugaison->temps = temps;
    conjugaison->word = word;
    return conjugaison;
}

void add_child_verbs(p_node_verbs parent, p_node_verbs child)
{
    if (parent->nb_children < MAX)
    {
        parent->children[parent->nb_children] = child;
        parent->nb_children++;
    }
}

void add_conjugaison(p_node_verbs node, p_conjugaison conjugaison)
{
    if (node->nb_conjugaisons < 18)
    {
        node->conjugaisons[node->nb_conjugaisons] = conjugaison;
        node->nb_conjugaisons++;
    }
}