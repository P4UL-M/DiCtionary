#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"

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

p_node search(p_tree tree, char *noun)
{
    if (tree == NULL)
        return NULL;
    p_node current = NULL;
    p_child i = tree->children;
    while (i != NULL && current == NULL)
    {
        if (i->node->value == noun[0])
        {
            current = i->node;
        }
        i = i->next;
    };
    if (current == NULL)
        return NULL;
    for (int i = 1; noun[i] != '\0'; i++)
    {
        current = searchInChild(current, noun[i]);
        if (current == NULL)
            return NULL;
    }
    return current;
}

p_node randomNextLetter(p_child current)
{
    int letter = rand() % 26;
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
    while(returned==NULL){
        returned = randomNextLetter(tree->children);
    }
    return returned;
}

p_form according(p_tree tree, int form){
    p_node current_node= findRandom(tree);
    p_form current_form=current_node->forms;
    while(current_form->tag!=form){
        if(current_form->next==NULL){
            current_node= findRandom(tree);
            current_form=current_node->forms;
        }
        else{
        current_form=current_form->next;
        }
    }
    return current_form;
}

p_form getForm(p_node node, char *form)
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