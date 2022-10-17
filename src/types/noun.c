#include "nouns.h"
#include "stdlib.h"
#include "stdio.h"

// Path: src/types/noun.c
p_tree create_tree()
{
    p_tree tree = malloc(sizeof(tree));
    tree->children = malloc(sizeof(p_node) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        tree->children[i] = NULL;
    }
    tree->nb_children = 0;
    return tree;
}

p_node create_node(char val)
{
    p_node node = malloc(sizeof(node));
    node->val = val;
    node->children = malloc(sizeof(p_node) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        node->children[i] = NULL;
    }
    node->nb_child = 0;
    node->declinaisons = malloc(sizeof(p_declinaison) * 4);
    for (int i = 0; i < 4; i++)
    {
        node->declinaisons[i] = NULL;
    }
    node->nb_declinaisons = 0;
    return node;
}

p_declinaison create_declinaison(t_forme forme, char *word)
{
    p_declinaison declinaison = malloc(sizeof(declinaison));
    declinaison->forme = forme;
    declinaison->word = word;
    return declinaison;
}

void add_child(p_node parent, p_node child)
{
    if (parent->nb_child < MAX)
    {
        parent->children[parent->nb_child] = child;
        parent->nb_child++;
    }
}

void add_declinaison(p_node node, p_declinaison declinaison)
{
    if (node->nb_declinaisons < 4)
    {
        node->declinaisons[node->nb_declinaisons] = declinaison;
        node->nb_declinaisons++;
    }
}