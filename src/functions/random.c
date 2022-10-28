#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"

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
