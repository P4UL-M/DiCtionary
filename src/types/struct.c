/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the structures*/
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

p_tree create_tree()
{
    p_tree tree = malloc(sizeof(t_tree));
    tree->children = NULL;
    return tree;
}

void add_child(p_node parent, char letter)
{
    if (parent->children == NULL)
    {
        p_child child = malloc(sizeof(t_child));
        child->node = malloc(sizeof(t_node));
        child->node->value = letter;
        child->node->children = NULL;
        parent->children = child;
        return;
    }
    p_child current = parent->children;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(t_child));
    current->next->node = malloc(sizeof(t_node));
    current->next->node->value = letter;
    current->next->node->children = NULL;
    return;
}

void add_child_to_tree(p_tree tree, char letter)
{
    if (tree->children == NULL)
    {
        p_child child = malloc(sizeof(t_child));
        child->node = malloc(sizeof(t_node));
        child->node->value = letter;
        child->node->children = NULL;
        tree->children = child;
        return;
    }
    p_child current = tree->children;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(t_child));
    current->next->node = malloc(sizeof(t_node));
    current->next->node->value = letter;
    current->next->node->children = NULL;
    return;
}

void add_form(p_node node, char *word, char *tag)
{
    if (node->forms == NULL)
    {
        node->forms = malloc(sizeof(t_form));
        node->forms->word = word;
        node->forms->tag = tag;
        return;
    }
    p_form current = node->forms;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(t_form));
    current->next->word = word;
    current->next->tag = tag;
    return;
}