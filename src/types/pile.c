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

int countFPile(p_fpile pile)
{
    int count = 0;
    p_form current = pile->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void enpileForm(p_fpile pile, p_form value)
{
    p_form form = (p_form)malloc(sizeof(t_form));
    form->next = pile->head;
    form->word = value->word;
    form->tag = value->tag;
    pile->head = form;
    return;
}

p_fpile createEmptyFPile()
{
    p_fpile pile = (p_fpile)malloc(sizeof(t_fpile));
    pile->head = NULL;
    return pile;
}

void displayPForm(p_form form)
{
    if (form->next != NULL)
    {
        displayPForm(form->next);
    }
    printf("%s", form->word);
}

void displayFPile(p_fpile pile)
{
    if (pile->head == NULL)
    {
        printf("Empty pile\n");
        return;
    }
    printf("current word is : '");
    displayPForm(pile->head);
    printf("'\n");
}

p_form depileForm(p_fpile pile)
{
    if (pile->head == NULL)
        return NULL;
    p_form form = pile->head;
    pile->head = pile->head->next;
    return form;
}
