/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the structures*/
#include "intTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

p_itree create_itree()
{
    p_itree tree = malloc(sizeof(t_itree));
    tree->children = NULL;
    return tree;
}

p_inode add_ichild(p_inode parent, int number)
{
    p_ichild child = malloc(sizeof(t_ichild));
    if (parent->children == NULL)
    {
        parent->children = child;
    }
    else
    {
        p_ichild current = parent->children;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = child;
    }
    // attribute of the child struct
    child->node = malloc(sizeof(t_inode));
    child->next = NULL;
    // attribute of the node struct
    child->node->value = number;
    child->node->children = NULL;
    return child->node;
}

p_inode add_ichild_to_itree(p_itree tree, int number)
{
    p_ichild child = malloc(sizeof(t_ichild));
    if (tree->children == NULL)
    {
        tree->children = child;
    }
    else
    {
        p_ichild current = tree->children;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = child;
    }
    // attribute of the child struct
    child->node = malloc(sizeof(t_inode));
    child->next = NULL;
    // attribute of the node struct
    child->node->value = number;
    child->node->children = NULL;
    return child->node;
}
