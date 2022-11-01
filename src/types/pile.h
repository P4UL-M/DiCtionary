/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse*/
#ifndef PILE_H
#define PILE_H
#include <stdbool.h>
#include "struct.h"

typedef struct s_child t_pnode, *p_pnode;

typedef struct s_pile
{
    struct s_child *head;

} t_pile, *p_pile;

p_pile createEmptyPile();
void enpile(p_pile, p_node);
p_node depile(p_pile);
bool isEmpty();
void displayPile(p_pile);

#endif