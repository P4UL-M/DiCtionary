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
    p_tree pronouns;
    p_tree determinants;
} t_dictionary, *p_dictionary;

typedef struct s_inputWord
{
    wchar_t *word;
    wchar_t *base;
    wchar_t *flags;
    wchar_t *type;
} t_inputWord, *p_inputWord;

typedef struct s_line
{
    wchar_t line[MAX_SIZE_LINE];
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
wchar_t **extractWord(wchar_t *);
void updateFile(char *, t_inputWord);
void addInTree(p_tree tree, wchar_t *word, wchar_t *base, int tag);
unsigned int getFlags(wchar_t *tag);

#endif