/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the structures*/
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

p_tree create_tree()
{
    p_tree tree = malloc(sizeof(t_tree));
    tree->children = NULL;
    tree->ponderation = 0;
    tree->forms = NULL;
    return tree;
}

p_node add_child(p_node parent, char letter)
{
    p_child child = malloc(sizeof(t_child));
    if (parent->children == NULL)
    {
        parent->children = child;
        child->next = NULL;
    }
    else
    {
        child->next = parent->children;
        parent->children = child;
    }
    // attribute of the child struct
    child->node = malloc(sizeof(t_node));
    // attribute of the node struct
    child->node->value = letter;
    child->node->ponderation = 0;
    child->node->children = NULL;
    child->node->forms = NULL;
    return child->node;
}

p_node get_child(p_node parent, char letter)
{
    p_child current = parent->children;
    while (current != NULL)
    {
        if (current->node->value == letter)
        {
            return current->node;
        }
        current = current->next;
    }
    return NULL;
}

int countForms(p_node node)
{
    int count = 0;
    p_form current = node->forms;
    if (current != NULL)
    {
        count++;
    }
    return count;
}

void addForm(p_node node, char *word, int tag)
{
    p_form current = malloc(sizeof(t_form));
    if (node->forms == NULL)
    {
        node->forms = current;
        current->next = NULL;
    }
    else
    {
        current->next = node->forms;
        node->forms = current;
    }
    current->word = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(current->word, word);
    current->tag = tag;
    return;
}