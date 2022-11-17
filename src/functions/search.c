/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains all searching functions*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../types/pile.h"
#include "../library/cache.h" // TODO : give credit for library (uhash owner and us in last project)

p_node searchInChild(p_node parent, wchar_t myChar)
// Search in all direct childs of parent for the char myChar
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

// useless with true search which found the word with the same perfomance even with base form
p_node search(p_tree tree, wchar_t *word)
// Search in only base forms
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
    for (int i = 1; word[i] != L'\0'; i++)
    {
        current = searchInChild(current, word[i]);
        if (current == NULL)
            return NULL;
    }
    return current;
}

p_form getForm(t_word word, wchar_t *form)
// Get the specific form of the word having its string
{
    p_form current = word.forms;
    while (current != NULL)
    {
        if (wcscmp(current->word, form) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

p_form getFormByTag(t_node node, int index)
// Get the specific form having its tag
{
    p_form current = node.forms;
    while (current != NULL)
    {
        if ((current->tag & index) == index)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

p_node depileSearch(p_pile pile, p_node node, wchar_t *word)
// Come back the nodes to find last occurrence
{
    if (node == NULL)
    {
        node = depile(pile);
    }
    if (find_entry(node)) // if already check
        return NULL;
    // search for our word in all child of our node
    // ideal is breath traversal but useless with recursion so prefix is the way to go
    p_form curr_form = node->forms;
    while (curr_form != NULL)
    {
        if (wcscmp(curr_form->word, word) == 0)
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
    add_entry(node);
    if (isEmpty(pile))
        return NULL;
    else
        return depileSearch(pile, NULL, word);
}

p_node trueSearch(p_tree tree, wchar_t *word)
// Search for the word recursively in the tree
{
    clear_cache();
    if (tree == NULL)
        return NULL;
    p_node current = tree;
    p_pile pile = createEmptyPile();
    enpile(pile, current);
    for (int i = 0; word[i] != '\0' && current != NULL; i++)
    {
        current = searchInChild(current, word[i]);
        if (current != NULL)
        {
            enpile(pile, current);
        }
    }
    p_node node = depileSearch(pile, NULL, word);
    return node;
}

p_word getWord(p_tree tree, wchar_t *word, bool truesearch)
// To get the word in tree with the word
{
    if (tree == NULL)
        return NULL;
    p_node current = NULL;
    if (truesearch)
        current = trueSearch(tree, word);
    else
        current = search(tree, word);
    if (current == NULL)
        return NULL;
    p_word result = (p_word)malloc(sizeof(t_word));
    result->forms = current->forms;
    result->base = getFormByTag(*current, Main_BIT);
    if (result->base == NULL)
    {
        result->base = result->forms;
    }
    return result;
}

void autocompletionAtNode(p_node node, p_fpile results)
// Get autocompletion results from the node
{
    if (node == NULL)
        return;
    if (results->size > 10)
        return;
    p_form main = getFormByTag(*node, Main_BIT);
    if (main != NULL)
    {
        enpileForm(results, main);
    }
    if (node->children != NULL)
    {
        for (p_child child = node->children; child != NULL; child = child->next)
        {
            autocompletionAtNode(child->node, results);
        }
    }
}

void autocompletion(p_tree tree, wchar_t *word, p_fpile result)
// Get the autocompletion of the word
{
    if (tree == NULL)
        return;
    p_node current = tree;
    for (int i = 0; word[i] != L'\0' && current != NULL; i++)
    {
        p_node currentChild = searchInChild(current, word[i]);
        if (currentChild == NULL)
            return;
        current = currentChild;
    }
    autocompletionAtNode(current, result);
}
