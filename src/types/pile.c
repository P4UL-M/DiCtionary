/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse*/
#include "struct.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

p_pile createEmptyPile()
{
    p_pile pile = (p_pile)malloc(sizeof(t_pile));
    pile->head = NULL;
    return pile;
}

bool isEmpty(p_pile pile)
{
    return pile->head == NULL;
}

void enpile(p_pile pile, p_node value)
{
    p_pnode node = (p_pnode)malloc(sizeof(t_pnode));
    node->next = pile->head;
    node->node = value;
    pile->head = node;
    return;
}

p_node depile(p_pile pile)
{
    if (isEmpty(pile))
        return NULL;
    p_node node = pile->head->node;
    pile->head = pile->head->next;
    return node;
}

void displayNode(p_pnode node)
{
    if (node->next != NULL)
    {
        displayNode(node->next);
    }
    printf("%c", node->node->value);
}

void displayPile(p_pile pile)
{
    if (isEmpty(pile))
    {
        printf("Empty pile\n");
        return;
    }
    printf("current word is : '");
    displayNode(pile->head);
    printf("'\n");
}