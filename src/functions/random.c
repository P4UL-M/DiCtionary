/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains all random functions*/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/random.h"
#include "../functions/search.h"
#include "../functions/dictionary.h"
#include "random.h"

int buildPonderation(p_node node)
// Calculate recursively the ponderation of the tree based on children nodes
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

void buildPonderations(t_dictionary dictionary)
// Calculate all ponderations of all trees
{
    buildPonderation(dictionary.nouns);
    buildPonderation(dictionary.adjectives);
    buildPonderation(dictionary.verbs);
    buildPonderation(dictionary.adverbs);
    buildPonderation(dictionary.pronouns);
    buildPonderation(dictionary.determinants);
}

p_node trueRandomNextLetter(p_node node)
// go recursively for the uniform random
{
    int ponderation = node->ponderation;
    float random = rand() / (float)RAND_MAX;
    random -= hasForms(node) / (float)ponderation;
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
// Efficient random
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

p_node randomNextLetter(p_node current)
// go recursively for the fast random
{
    int nbChild = countChildren(current);
    float random = rand() / (float)RAND_MAX;
    if (current->forms != NULL)
    {
        if ((current->children == NULL) || (rand() % 7 == 1))
        {
            return current;
        }
    }
    p_child nodeChild = current->children;
    while (random > (1 / (float)nbChild) && nodeChild->next != NULL)
    {
        random -= 1 / (float)nbChild;
        nodeChild = nodeChild->next;
    }
    return randomNextLetter(nodeChild->node);
}

p_node findRandom(p_tree tree)
// Find a random word with fast but not uniform way
{
    p_node returned = NULL;
    while (returned == NULL)
    {
        returned = randomNextLetter(tree);
    }
    return returned;
}

p_word getRandomWord(p_tree tree, bool trueSearchMode)
// call the random functions
{
    p_node node;
    if (trueSearchMode)
        node = trueRandom(tree);
    else
        node = findRandom(tree);
    p_word result = (p_word)malloc(sizeof(t_word));
    result->forms = node->forms;
    result->base = getFormByTag(*node, Main_BIT);
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
