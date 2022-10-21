/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types/nouns.h"
#include "types/verbs.h"
#include "functions/dictionary.h"
#include "menu/menu_main.h"

int main()
{
    /*clock_t t;
    t = clock();
    printf("Hello world\n");
    p_tree_adj tree = create_tree_noun();
    p_node_adj node = create_node_noun('a');
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
    p_tree_noun tree3 = create_tree_noun();
    extractFile("data/dictionnaire.txt", tree3);
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    extractFile("data/dictionnaire.txt", tree3);*/
    menu();
    return 0;
}