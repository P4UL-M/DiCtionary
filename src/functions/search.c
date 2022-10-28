#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../types/pile.h"
#include "../library/cache.h" // TODO : give credit for library (uhash owner and us in last project)

p_node searchInChild(p_node parent, char myChar)
{
    if (parent == NULL)
        return NULL;
    p_node current = NULL;
    p_child i = parent->children;
    while (i != NULL && current == NULL)
    {
        if (i->node->value == myChar)
        {
            current = i->node;
        }
        i = i->next;
    };
    return current;
}

p_node search(p_tree tree, char *word)
{
    if (tree == NULL)
        return NULL;
    p_node current = NULL;
    p_child i = tree->children;
    while (i != NULL && current == NULL)
    {
        if (i->node->value == word[0])
        {
            current = i->node;
        }
        i = i->next;
    };
    if (current == NULL)
        return NULL;
    for (int i = 1; word[i] != '\0'; i++)
    {
        current = searchInChild(current, word[i]);
        if (current == NULL)
            return NULL;
    }
    return current;
}

p_form getForm(p_word node, char *form)
{
    if (node == NULL)
        return NULL;
    p_form current = node->forms;
    while (current != NULL)
    {
        if (strcmp(current->word, form) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

p_node depileSearch(p_pile pile, p_node node, char *word)
{
    if (node == NULL)
    {
        node = dequeue(pile);
    }
    if (find_entry((int)node) != NULL) // if already check
    {
        return NULL;
    }
    // search for our word in all child of our node
    // ideal is breath traversal but useless with recursion so prefix is the way to go
    p_form curr_form = node->forms;
    while (curr_form != NULL)
    {
        if (strcmp(curr_form->word, word) == 0)
        {
            return node;
        }
        curr_form = curr_form->next;
    }
    if (node->children != NULL)
    {
        for (p_child child = node->children; child != NULL; child = child->next)
        {
            p_node child_node = depileSearch(pile, child->node, word);
            if (child_node != NULL)
            {
                return child_node;
            }
        }
    }
    add_entry((int)node, node);
    if (isEmpty(pile))
        return NULL;
    else
        return depileSearch(pile, NULL, word);
}

p_node trueSearch(p_tree tree, char *word)
{
    if (tree == NULL)
        return NULL;
    p_node current = NULL;
    p_child i = tree->children;
    p_pile pile = createEmptyPile();
    while (i != NULL && current == NULL)
    {
        if (i->node->value == word[0])
        {
            current = i->node;
        }
        i = i->next;
    };
    if (current == NULL)
        return NULL;
    enqueue(pile, current);
    for (int i = 1; word[i] != '\0'; i++)
    {
        current = searchInChild(current, word[i]);
        if (current == NULL)
        {
            p_node node = depileSearch(pile, NULL, word);
            return node;
        }
        enqueue(pile, current);
    }
    return current;
}

p_word getWord(p_tree tree, char *word)
{
    if (tree == NULL)
        return NULL;
    p_node current = search(tree, word);
    if (current == NULL)
    {
        current = trueSearch(tree, word);
        if (current == NULL)
            return NULL;
        p_word result = malloc(sizeof(t_word));
        result->base = malloc(sizeof(char) * (strlen(word) + 1));
        strcpy(result->base, word);
        result->forms = current->forms;
        return result;
    }
    p_word result = malloc(sizeof(t_word));
    result->base = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(result->base, word);
    result->forms = current->forms;
    return result;
}
