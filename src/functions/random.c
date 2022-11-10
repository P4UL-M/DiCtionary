#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/random.h"
#include "../functions/search.h"
#include "random.h"

int buildPonderation(p_node node)
{
    if (node == NULL)
    {
        return 0;
    }
    int nbWord = 0;
    for (p_child childNode = node->children; childNode != NULL; childNode = childNode->next)
    {
        nbWord += buildPonderation(childNode->node);
    }
    node->ponderation = nbWord + hasForms(node);
    return node->ponderation;
}

p_node trueRandomNextLetter(p_node node)
{
    int ponderation = node->ponderation;
    // int random = pcg32_boundedrand((int32_t)ponderation + 1);
    float random = rand() / (float)RAND_MAX;
    random -= hasForms(node);
    if (node->forms != NULL && random <= 0)
    {
        return node;
    }
    p_child nodeChild = node->children;
    while (random > nodeChild->node->ponderation / (float)ponderation && nodeChild->next != NULL)
    {
        random -= nodeChild->node->ponderation / (float)ponderation;
        nodeChild = nodeChild->next;
    }
    return trueRandomNextLetter(nodeChild->node);
}

p_node trueRandom(p_tree dico)
{
    int ponderation = dico->ponderation;
    float random = rand() / (float)RAND_MAX;
    p_child nodeChild = dico->children;
    while (random > nodeChild->node->ponderation / (float)ponderation && nodeChild->next != NULL)
    {
        random -= nodeChild->node->ponderation / (float)ponderation;
        nodeChild = nodeChild->next;
    }
    return trueRandomNextLetter(nodeChild->node);
}

p_node randomNextLetter(p_child current)
{
    int letter = rand() % countChildren(current->node);
    for (int i = 0; (i < letter) && (current->next != NULL); i++)
    {
        current = current->next;
    }
    if (current->node->forms != NULL)
    {
        if ((current->node->children == NULL) || (rand() % 7 == 1))
        {
            return current->node;
        }
    }
    return randomNextLetter(current->node->children);
}

p_node findRandom(p_tree tree)
{
    p_node returned = NULL;
    while (returned == NULL)
    {
        returned = randomNextLetter(tree->children);
    }
    return returned;
}

// TODO : rewrite this function
p_form according(p_tree tree, int form)
{
    p_node current_node = findRandom(tree);
    p_form current_form = current_node->forms;
    while (current_form->tag != form)
    {
        if (current_form->next == NULL)
        {
            current_node = findRandom(tree);
            current_form = current_node->forms;
        }
        else
        {
            current_form = current_form->next;
        }
    }
    return current_form;
}

p_word getRandomWord(p_tree tree, bool trueSearchMode)
{
    p_node node;
    if (trueSearchMode)
        node = trueRandom(tree);
    else
        node = findRandom(tree);
    p_word result = malloc(sizeof(t_word));
    result->forms = node->forms;
    result->base = getFormByIndex(node, Main_BIT);
    if (result->base == NULL)
    {
        result->base = result->forms;
    }
    return result;
}

// Here is another algorithm to generate random words
// This one isn't used in the program because it has very bad performances but has the advantage of being very simple and perfectly uniform
// p_node prefix_traversal(p_node node, int *stop)
// {
//     if (hasForms(node) > 0)
//     {
//         (*stop)--;
//         if (*stop < 0)
//         {
//             return node;
//         }
//     }

//     p_node result = NULL;
//     p_child child = node->children;
//     while (result == NULL && child != NULL)
//     {
//         result = prefix_traversal(child->node, stop);
//         child = child->next;
//     }
//     return result;
// }

// p_node experimentalTrueRandom(p_tree tree)
// {
//     int ponderation = tree->ponderation;
//     int random = rand() % ponderation;
//     return prefix_traversal(tree, &random);
// }