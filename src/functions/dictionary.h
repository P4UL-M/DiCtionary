/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../types/struct.h"
#include "../types/constants.h"

#define NB_LINES 287977
#define MAX_SIZE_LINE 256

typedef struct dictionary
{
    p_tree nouns;
    p_tree adjectives;
    p_tree adverbs;
    p_tree verbs;
} t_dictionary, *p_dictionary;

typedef struct s_inputWord
{
    char *word;
    char *base;
    char *flags;
    char *type;
} t_inputWord, *p_inputWord;

typedef struct s_line
{
    char line[MAX_SIZE_LINE];
    struct s_line *next;
    struct s_line *prev;

} t_line, *p_line;

typedef struct s_buffer
{
    p_line first;
    p_line last;
    int size;
} t_buffer, *p_buffer;

t_dictionary extractFile(char *);
char **extractWord(char *);
void updateFile(char *, t_inputWord);
void addInTree(p_tree tree, char *word, char *base, int tag);
int getFlags(char *tag);

#endif