/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions for the structures*/
#ifndef struct_h
#define struct_h

typedef struct s_form
{
    char *word;
    int tag;
    struct s_form *next;
} t_form, *p_form;

typedef struct s_node
{
    char value;
    int ponderation;
    struct s_form *forms;
    struct s_child *children;
} t_node, *p_node;

typedef struct s_child
{
    struct s_node *node;
    struct s_child *next;
} t_child, *p_child;

typedef struct s_node t_tree, *p_tree;

typedef struct t_word
{
    struct s_form *base;
    struct s_form *forms;
} t_word, *p_word;

p_tree create_tree();
p_node add_child(p_node, char);
int countForms(p_node);
int hasForms(p_node);
int countChildren(p_node);
void addForm(p_node, char *, int);
p_node get_child(p_node, char);

#endif