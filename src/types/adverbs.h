#ifndef adverbs_h
#define adverbs_h

#define MAX 26 // only 26 letters (take into account accent later)
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

p_tree_adv create_tree_adv();

p_node_adv createnode_adv(char val);

void add_child_adv(p_node_adv parent, p_node_adv child);

#endif