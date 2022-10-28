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
    return tree;
}

p_node add_child(p_node parent, char letter)
{
    if ((int)letter < 0)
    {
        printf("NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
    }
    if (parent->children == NULL)
    {
        p_child child = malloc(sizeof(t_child));
        parent->children = child;
        // attribute of the child struct
        child->node = malloc(sizeof(t_node));
        child->next = NULL;
        // attribute of the node struct
        child->node->value = letter;
        child->node->children = NULL;
        child->node->forms = NULL;
        return child->node;
    }
    p_child current = parent->children;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(t_child));
    // attribute of the child struct
    current->next->node = malloc(sizeof(t_node));
    current->next->next = NULL;
    // attribute of the node struct
    current->next->node->value = letter;
    current->next->node->children = NULL;
    current->next->node->forms = NULL;
    return current->next->node;
}

p_node add_child_to_tree(p_tree tree, char letter)
{
    if (tree->children == NULL)
    {
        p_child child = malloc(sizeof(t_child));
        tree->children = child;
        // attribute of the child struct
        child->node = malloc(sizeof(t_node));
        child->next = NULL;
        // attribute of the node struct
        child->node->value = letter;
        child->node->children = NULL;
        child->node->forms = NULL;
        return child->node;
    }
    p_child current = tree->children;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(t_child));
    // attribute of the child struct
    current->next->node = malloc(sizeof(t_node));
    current->next->next = NULL;
    // attribute of the node struct
    current->next->node->value = letter;
    current->next->node->children = NULL;
    current->next->node->forms = NULL;
    return current->next->node;
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

p_node get_child_from_tree(p_tree tree, char letter)
{
    p_child current = tree->children;
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

void addForm(p_node node, char *word, int tag)
{
    if (node->forms == NULL)
    {
        node->forms = malloc(sizeof(t_form));
        node->forms->word = malloc(sizeof(char) * (strlen(word) + 1));
        strcpy(node->forms->word, word);
        node->forms->tag = tag;
        node->forms->next = NULL;
        return;
    }
    p_form current = node->forms;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(t_form));
    current->next->word = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(current->next->word, word);
    current->next->tag = tag;
    current->next->next = NULL;
    return;
}