/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the nouns*/
#ifndef noun_h
#define noun_h

#include <stdbool.h>

#define MAX 26 // only 26 letters (take into account accent later)
#define MAX_DECL 4
#define NOUN_TYPE "Nom"
#define ADJECTIVE_TYPE "Adj"

typedef enum forme_noun
{
    Mas_SG,
    Fem_SG,
    Mas_PL,
    Fem_PL,
} t_forme_noun;

typedef struct form_noun t_forme_adj;

typedef struct declinaison_noun
{
    t_forme_noun forme;
    char *word;
} t_declinaison_noun, *list_declinaison_noun;

typedef struct declinaison_noun t_declinaison_adj, *list_declinaison_adj;

typedef struct node_noun
{
    char value;
    list_declinaison_noun declinaisons;
    int nb_declinaisons;
    struct node_noun **children;
    int nb_children;
} t_node_noun, *p_node_noun;

typedef struct node_noun t_node_adj, *p_node_adj;

typedef struct tree_noun
{
    p_node_noun *children;
    int nb_children;
} t_tree_noun, *p_tree_noun;

typedef struct tree_noun t_tree_adj, *p_tree_adj;

typedef struct version_noun
{
    char *word;
    t_forme_noun forme;
    list_declinaison_noun declinaisons;
} t_version_noun, *p_version_noun;

typedef struct version_noun t_version_adj, *p_version_adj;

p_tree_noun create_tree_noun();
p_node_noun create_node_noun(char val);
t_declinaison_noun create_declinaison(t_forme_noun forme, char *word);
bool add_child(p_node_noun parent, p_node_noun child);
bool add_declinaison(p_node_noun node, t_declinaison_noun declinaison);

#endif