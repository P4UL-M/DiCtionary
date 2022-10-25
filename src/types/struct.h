/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the structures*/
#ifndef struct_h
#define struct_h
#include <stdbool.h>

typedef struct s_form
{
    char *word;
    char *tag;
    struct s_form *next;
} t_form, *p_form;

typedef struct s_node
{
    char value;
    struct s_form *forms;
    struct s_child *children;
} t_node, *p_node;

typedef struct s_child
{
    struct s_node *node;
    struct s_child *next;
} t_child, *p_child;

typedef struct s_tree
{
    struct s_child *children;
} t_tree, *p_tree;

p_tree create_tree();
void add_child(p_node parent, char letter);
void add_child_to_tree(p_tree tree, char letter);
void add_form(p_node node, char *word, char *tag);

#endif