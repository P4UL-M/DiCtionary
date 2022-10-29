#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../types/intTree.h"
#include "random.h"

int buildPonderation(p_node dicoNode, p_inode ponderationNode)
{
    if (dicoNode == NULL)
    {
        return 0;
    }
    int nbWord = 0;
    for (p_child childNode = dicoNode->children; childNode != NULL; childNode = childNode->next)
    {
        p_inode cPonderationNode = add_ichild(ponderationNode, 0);
        nbWord += buildPonderation(childNode->node, cPonderationNode);
    }
    ponderationNode->value = nbWord + countForms(dicoNode);
    return ponderationNode->value;
}

p_itree createPonderationTree(p_tree dico)
{
    p_itree ponderationTree = create_itree();
    for (p_child childNode = dico->children; childNode != NULL; childNode = childNode->next)
    {
        p_inode node = add_ichild_to_itree(ponderationTree, 0);
        node->value = countForms(childNode->node) + buildPonderation(childNode->node, node);
    }
    return ponderationTree;
}

p_node trueRandomNextLetter(p_node node, p_inode ponderation)
{
    int random = rand() % ponderation->value;
    if (node->forms != NULL && random <= countForms(node))
    {
        return node;
    }
    p_child nodeChild = node->children;
    p_ichild ponderationChild = ponderation->children;
    while (random > ponderationChild->node->value)
    {
        random -= ponderationChild->node->value;
        nodeChild = nodeChild->next;
        ponderationChild = ponderationChild->next;
    }
    return trueRandomNextLetter(nodeChild->node, ponderationChild->node);
}

p_node trueRandom(p_tree dico, p_itree ponderationTree)
{
    int ponderation = 0;
    for (p_ichild childNode = ponderationTree->children; childNode != NULL; childNode = childNode->next)
    {
        ponderation += childNode->node->value;
    }
    int random = rand() % ponderation;
    p_child nodeChild = dico->children;
    p_ichild ponderationChild = ponderationTree->children;
    while (random > ponderationChild->node->value)
    {
        random -= ponderationChild->node->value;
        nodeChild = nodeChild->next;
        ponderationChild = ponderationChild->next;
    }
    return trueRandomNextLetter(nodeChild->node, ponderationChild->node);
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
    srand(time(NULL));
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
