/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the adverbs*/
#ifndef adverbs_h
#define adverbs_h

#define MAX 30
#define ADVERB_TYPE "Adv"

typedef struct node_adv
{
    char val;
    struct node_adv **children;
    int nb_child;
} t_node_adv, *p_node_adv;

typedef struct tree_adv
{
    p_node_adv *children;
    int nb_children;
} t_tree_adv, *p_tree_adv;

typedef struct version_adv
{
    char *word;
} t_version_adv, *p_version_adv;

p_tree_adv create_tree_adv();

p_node_adv createnode_adv(char val);

void add_child_adv(p_node_adv parent, p_node_adv child);

#endif