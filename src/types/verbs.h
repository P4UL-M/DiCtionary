/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the verbs*/
#ifndef verb_h
#define verb_h

#include <stdbool.h>

#define MAX 30
#define MAX_CONJUG 18
#define VERB_TYPE "Ver"

typedef enum personne
{
    SG_P1,
    SG_P2,
    SG_P3,
    PL_P1,
    PL_P2,
    PL_P3
} t_personne;

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
} t_temps;

typedef struct conjugaison
{
    t_personne personne;
    t_temps temps;
    char *word;
} t_conjugaison, *list_conjugaison;

typedef struct node_verb
{
    char value;
    list_conjugaison conjugaisons;
    int nb_conjugaisons;
    struct node_verb **children;
    int nb_children;
} t_node_verb, *p_node_verb;

typedef struct tree_verb
{
    p_node_verb *children;
    int nb_children;
} t_tree_verb, *p_tree_verb;

typedef struct version_verb
{
    char *word;
    t_conjugaison conj;
    list_conjugaison conjugaisons;
} t_version_verb, *p_version_verb;

p_tree_verb create_tree_verb();
p_node_verb create_node_verb(char val);
t_conjugaison create_conjugaison(t_personne pers, t_temps temps, char *word);
bool add_child_verb(p_node_verb parent, p_node_verb child);
bool add_conjugaison(p_node_verb node, t_conjugaison conjugaison);

#endif