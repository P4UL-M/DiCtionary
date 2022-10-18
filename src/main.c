#include <stdlib.h>
#include <stdio.h>
#include "types/nouns.h"
#include "types/verbs.h"

int main()
{
    printf("Hello world\n");
    p_tree_noun tree = create_tree_noun();
    p_node_noun node = create_node_noun('a');
    t_declinaison_noun declinaison = create_declinaison(Mas_SG, "test");
    add_declinaison(node, declinaison);
    tree->children[0] = node;
    tree->nb_children++;
    printf("%c, %s, %d\n", tree->children[0]->value, tree->children[0]->declinaisons[0].word, tree->nb_children);
    printf("Hello world 2\n");
    p_tree_verb tree2 = create_tree_verb();
    p_node_verb node2 = create_node_verb('a');
    t_conjugaison conjugaison = create_conjugaison(SG_P1, IPre, "test");
    add_conjugaison(node2, conjugaison);
    tree2->children[0] = node2;
    tree2->nb_children++;
    printf("%c, %s, %d\n", tree2->children[0]->value, tree2->children[0]->conjugaisons[0].word, tree2->nb_children);
    return 0;
}