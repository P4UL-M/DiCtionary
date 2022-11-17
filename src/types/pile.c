/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains functions for stack gestion*/
#include "struct.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

p_pile createEmptyPile()
// To create an empty stack
{
    p_pile pile = (p_pile)malloc(sizeof(t_pile));
    pile->head = NULL;
    return pile;
}

bool isEmpty(p_pile pile)
// To check if the stask is empty
{
    return pile->head == NULL;
}

void enpile(p_pile pile, p_node value)
// To add a value to the stack
{
    p_pnode node = (p_pnode)malloc(sizeof(t_pnode));
    node->next = pile->head;
    node->node = value;
    pile->head = node;
    return;
}

p_node depile(p_pile pile)
// To unstack
{
    if (isEmpty(pile))
        return NULL;
    p_node node = pile->head->node;
    pile->head = pile->head->next;
    return node;
}

void displayNode(p_pnode node)
// To display node of a pile
{
    if (node->next != NULL)
    {
        displayNode(node->next);
    }
    wprintf(L"%c", node->node->value);
}

void displayPile(p_pile pile)
// To display a pile
{
    if (isEmpty(pile))
    {
        wprintf(L"Empty pile\n");
        return;
    }
    wprintf(L"current word is : '");
    displayNode(pile->head);
    wprintf(L"'\n");
}

void enpileForm(p_fpile pile, p_form value)
// To stack with second type stack
{
    p_form form = (p_form)malloc(sizeof(t_form));
    form->next = pile->head;
    form->word = value->word;
    form->tag = value->tag;
    pile->head = form;
    pile->size++;
    return;
}

p_fpile createEmptyFPile()
// To create empty second type stack
{
    p_fpile pile = (p_fpile)malloc(sizeof(t_fpile));
    pile->head = NULL;
    pile->size = 0;
    return pile;
}

void displayFPile(p_fpile pile)
// To display second type stack
{
    if (pile->head == NULL)
    {
        wprintf(L"Empty pile\n");
        return;
    }
    else
    {
        p_form temp = pile->head;
        while (temp != NULL)
        {
            wprintf(L"%ls, ", temp->word);
            temp = temp->next;
        }
    }
    wprintf(L"\b\b  \b\b\n");
}

p_form depileForm(p_fpile pile)
// To unstack second type stack
{
    if (pile->head == NULL)
        return NULL;
    p_form form = pile->head;
    pile->head = pile->head->next;
    return form;
}

void freeFPile(p_fpile pile)
// To free second type stack
{
    p_form form = NULL;
    while ((form = depileForm(pile)) != NULL)
    {
        free(form);
    }
    free(pile);
}
