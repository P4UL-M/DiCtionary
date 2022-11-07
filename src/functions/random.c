#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/random.h"
#include "../functions/search.h"
#include "random.h"
#include "../library/pcg_basic.h"

pcg32_random_t seed = (pcg32_random_t)PCG32_INITIALIZER;

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
    node->ponderation = nbWord + countForms(node);
    return node->ponderation;
}

p_node trueRandomNextLetter(p_node node)
{
    int ponderation = node->ponderation;
    int random = pcg32_boundedrand((int32_t)ponderation + 1);
    random -= countForms(node);
    if (node->forms != NULL && random <= 0)
    {
        return node;
    }
    p_child nodeChild = node->children;
    while (random > nodeChild->node->ponderation)
    {
        random -= nodeChild->node->ponderation;
        nodeChild = nodeChild->next;
    }
    return trueRandomNextLetter(nodeChild->node);
}

p_node prefix_traversal(p_node node, int *stop)
{
    if (countForms(node) > 0)
    {
        (*stop)--;
        if (*stop < 0)
        {
            return node;
        }
    }

    p_node result = NULL;
    p_child child = node->children;
    while (result == NULL && child != NULL)
    {
        result = prefix_traversal(child->node, stop);
        child = child->next;
    }
    return result;
}

p_node experimentalTrueRandom(p_tree tree)
{
    int ponderation = tree->ponderation;
    int random = rand() % ponderation;
    // prefix traversal
    return prefix_traversal(tree, &random);
}

p_node trueRandom(p_tree dico)
{
    int ponderation = dico->ponderation;
    int random = pcg32_boundedrand((int32_t)ponderation + 1);
    p_child nodeChild = dico->children;
    while (random > nodeChild->node->ponderation)
    {
        random -= nodeChild->node->ponderation;
        nodeChild = nodeChild->next;
    }
    return trueRandomNextLetter(nodeChild->node);
}

p_node randomNextLetter(p_child current)
{
    int letter = rand() % 26; // TODO : use nbChild
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

p_word getRandomWord(p_tree tree, int randomLevel)
{
    p_node node;
    if (randomLevel == 1)
        node = trueRandom(tree);
    else if (randomLevel == 2)
        node = experimentalTrueRandom(tree);
    else
        node = findRandom(tree);
    p_word result = malloc(sizeof(t_word));
    result->forms = node->forms;
    p_form main = getFormByIndex(node, Main_BIT);
    result->base = malloc(sizeof(char) * (main ? (strlen(main->word) + 1) : (strlen(node->forms->word) + 1)));
    strcpy(result->base, main ? main->word : node->forms->word);
    return result;
}