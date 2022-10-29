#ifndef intTree_h
#define intTree_h

typedef struct s_inode
{
    int value;
    struct s_ichild *children;
} t_inode, *p_inode;

typedef struct s_ichild
{
    struct s_inode *node;
    struct s_ichild *next;
} t_ichild, *p_ichild;

typedef struct s_itree
{
    struct s_ichild *children;
} t_itree, *p_itree;

p_itree create_itree();
p_inode add_ichild(p_inode parent, int number);
p_inode add_ichild_to_itree(p_itree tree, int number);

#endif