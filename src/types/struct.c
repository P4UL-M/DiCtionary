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
    p_child child = malloc(sizeof(t_child));
    if (parent->children == NULL)
    {
        parent->children = child;
    }
    else
    {
        p_child current = parent->children;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = child;
    }
    // attribute of the child struct
    child->node = malloc(sizeof(t_node));
    child->next = NULL;
    // attribute of the node struct
    child->node->value = letter;
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
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
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