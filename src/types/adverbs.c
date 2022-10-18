#include "adverbs.h"
#include <stdio.h>
#include <stdlib.h>

p_tree_adv create_tree_adv(){
    p_tree_adv tree = malloc(sizeof(tree));
    tree->children = malloc(sizeof(p_node_adv) * MAX);
    for (int i = 0; i < MAX; i++)
    {
        tree->children[i] = NULL;
    }
    tree->nb_children = 0;
    return tree;
}

p_node_adv createnode_adv(char val){
    p_node_adv n=malloc(sizeof(p_node_adv)*MAX);
    n->val=val;
    n->nb_child=MAX;
    for (int i = 0; i < MAX; i++)
    {
        n->children[i] = NULL;
    }
}

void add_child_adv(p_node_adv parent, p_node_adv child)
{
    if (parent->nb_child < MAX)
    {
        parent->children[parent->nb_child] = child;
        parent->nb_child++;
    }
}