#ifndef noun_h
#define noun_h

#include <stdbool.h>

#define MAX 26 // only 26 letters (take into account accent later)
#define MAX_DECL 4

typedef enum forme_noun
{
    Mas_SG,
    Fem_SG,
    Mas_PL,
    Fem_PL,
} t_forme_noun;

typedef struct declinaison_noun
{
    t_forme_noun forme;
    char *word;
} t_declinaison_noun, *p_declinaison_noun;

typedef struct node
{
    char values;
    t_declinaison_noun *declinaisons;
    int nb_declinaisons;
    struct node **children;
    int nb_children;
} t_node_noun, *p_node_noun;

typedef struct tree
{
    p_node_noun *children;
    int nb_children;
} t_tree_noun, *p_tree_noun;

p_tree_noun create_tree();
p_node_noun create_node(char val);
t_declinaison_noun create_declinaison(t_forme_noun forme, char *word);
bool add_child(p_node_noun parent, p_node_noun child);
bool add_declinaison(p_node_noun node, t_declinaison_noun declinaison);

#endif