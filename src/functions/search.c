#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/struct.h"
#include "../types/constants.h"

p_node searchInChild(p_node parent, char myChar)
{
    if (parent == NULL)
    {
        return NULL;
    }
    if (parent->children == NULL)
        return NULL;
    p_node current = NULL;
    p_child i = parent->children;
    do
    {
        if (i->node->value == myChar)
        {
            current = i->node;
        }
        i = i->next;
    } while (i != NULL && current == NULL);
    return current;
}

p_node search(p_tree tree, char *noun)
{
    if (tree == NULL)
    {
        return NULL;
    }
    p_node current = NULL;
    p_child i = tree->children;
    do
    {
        if (i->node->value == noun[0])
        {
            current = i->node;
        }
        i = i->next;
    } while (i != NULL && current == NULL);
    if (current == NULL)
    {
        return NULL;
    }
    for (int i = 1; noun[i] != '\0'; i++)
    {
        current = searchInChild(current, noun[i]);
        if (current == NULL)
        {
            return NULL;
        }
    }
    return current;
}

/*p_node findRandom(p_tree tree){
    srand(time(NULL));
    return randomNextLetter(tree->children);
}

p_node randomNextLetter(p_child current){
    int letter=rand()%26;
    for(int i=0;(i<letter) && (current->next!=NULL);i++){
        current=current->next;
    }
    if((current->node->form!=NULL){
        if((current->node->children==NULL)||(rand()%7==1)){
            return current->node;
        }
    }
    randomNextLetter(current->node->children);
}*/