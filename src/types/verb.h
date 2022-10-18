#ifndef verb_h
#define verb_h

#include <stdbool.h>

#define MAX 26 // only 26 letters (take into account accent later)
#define MAX_CONJUG 18

typedef enum personne
{
    SG_P1,
    SG_P2,
    SG_P3,
    PL_P1,
    PL_P2,
    PL_P3
} t_personne,
    *p_personne;

typedef enum temps
{
    IPre,
    IImp,
    SPre,
    IPsimp,
    PPre,
    SImp,
    PPas,
    IFut,
    CPre,
    Inf
} t_temps,
    *p_temps;

typedef struct conjugaison
{
    t_personne personne;
    t_temps temps;
    char *word;
} t_conjugaison, *p_conjugaison;

typedef struct node
{
    char value;
    t_conjugaison *conjugaisons;
    int nb_conjugaisons;
    struct node **children;
    int nb_children;
} t_node_verbs, *p_node_verbs;

typedef struct tree_verbs
{
    p_node_verbs *children;
    int nb_children;
} t_tree_verbs, *p_tree_verbs;

p_tree_verbs create_tree_verbs();
p_node_verbs create_node_verbs(char val);
t_conjugaison create_conjugaison(t_personne pers, t_temps temps, char *word);
bool add_child_verbs(p_node_verbs parent, p_node_verbs child);
bool add_conjugaison(p_node_verbs node, t_conjugaison conjugaison);

#endif