#ifndef noun_h
#define noun_h

#define MAX 26 // only 26 letters (take into account accent later)

typedef enum forme
{
    Mas_SG,
    Fem_SG,
    Mas_PL,
    Fem_PL,
} t_forme;

typedef struct declinaison
{
    t_forme forme;
    char *word;
} t_declinaison, *p_declinaison;

typedef struct node
{
    char val;
    p_declinaison *declinaisons;
    int nb_declinaisons;
    struct node **children;
    int nb_child;
} t_node, *p_node;

typedef struct tree
{
    p_node *children;
    int nb_children;
} t_tree, *p_tree;

p_tree create_tree();
p_node create_node(char val);
p_declinaison create_declinaison(t_forme forme, char *word);
void add_child(p_node parent, p_node child);
void add_declinaison(p_node node, p_declinaison declinaison);

#endif