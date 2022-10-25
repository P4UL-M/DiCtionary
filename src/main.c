/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types/struct.h"
#include "functions/dictionary.h"
//#include "menu/menu_main.h"
#include "functions/search.h"
#include "menu/menu_main.h"

int main()
{
    clock_t t;
    t = clock();
    printf("Hello world\n");
    p_tree tree = create_tree();
    add_child_to_tree(tree, '1');
    add_child_to_tree(tree, 'a');
    p_node current = tree->children->next->node;
    add_form(current, "a", "a");
    add_child(current, 'b');
    current = current->children->node;
    add_form(current, "b", "b");
    add_child(current, 'c');
    current = current->children->node;
    add_form(current, "c", "c");
    p_node result = search(tree, "abc");
    printf("%c %s %s\n", result->value, result->forms->tag, result->forms->word);
    menu();
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}