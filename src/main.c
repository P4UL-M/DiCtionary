#include <stdlib.h>
#include <stdio.h>
#include "types/nouns.h"

int main()
{
    printf("Hello world\n");
    p_tree_noun tree = create_tree();
    p_node_noun node = create_node('a');
    t_declinaison_noun declinaison = create_declinaison(Mas_SG, "test");
    add_declinaison(node, declinaison);
    tree->children[0] = node;
    tree->nb_children++;
    printf("%c, %s, %d", tree->children[0]->values, tree->children[0]->declinaisons[0].word, tree->nb_children);
    return 0;
}