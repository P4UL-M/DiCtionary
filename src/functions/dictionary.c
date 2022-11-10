/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#ifdef _WIN32
#define strtok_r(s, d, c) strtok_s(s, d, c)
char *strtok_s(char *str, const char *delimiters, char **context);
#endif
#include "dictionary.h"
#include "search.h"
#include "../types/struct.h"
#include "../types/constants.h"

char **extractWord(char *source)
{
    source[strcspn(source, "\n")] = 0;
    char **output = (char **)malloc(sizeof(char *) * 3);
    // separate the word, the base form and the type
    output[0] = strtok(source, "\t");
    output[1] = strtok(NULL, "\t");
    output[2] = strtok(NULL, "\t");
    return output;
}

p_node addBaseInTree(p_tree node, char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        p_node child = get_child(node, word[i]);
        if (child == NULL)
        {
            node = add_child(node, word[i]);
        }
        else
        {
            node = child;
        }
    }
    return node;
}

void addInTree(p_tree tree, char *word, char *base, int tag)
{
    p_node node = search(tree, base);
    if (node == NULL)
    {
        node = addBaseInTree(tree, base);
    }
    if (strcmp(word, base) == 0)
    {
        tag += Main_BIT;
    }
    addForm(node, word, tag);
}

int countChar(char *word, char c)
{
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == c)
        {
            count++;
        }
    }
    return count;
}

int getFlags(char *tag)
{
    char *saveptr1;
    char *flag = strtok_r(tag, "+", &saveptr1);
    int flags = 0;
    do
    {
        if (strcmp(flag, P1) == 0)
            flags += P1_BIT;
        else if (strcmp(flag, P2) == 0)
            flags += P2_BIT;
        else if (strcmp(flag, P3) == 0)
            flags += P3_BIT;
        else if (strcmp(flag, Mas) == 0)
            flags += Mas_BIT;
        else if (strcmp(flag, Fem) == 0)
            flags += Fem_BIT;
        else if (strcmp(flag, PL) == 0)
            flags += PL_BIT;
        else if (strcmp(flag, SG) == 0)
            flags += SG_BIT;
        else if (strcmp(flag, IPre) == 0)
            flags += IPre_BIT;
        else if (strcmp(flag, IImp) == 0)
            flags += IImp_BIT;
        else if (strcmp(flag, SPre) == 0)
            flags += SPre_BIT;
        else if (strcmp(flag, IPSim) == 0)
            flags += IPSim_BIT;
        else if (strcmp(flag, PPre) == 0)
            flags += PPre_BIT;
        else if (strcmp(flag, SImp) == 0)
            flags += SImp_BIT;
        else if (strcmp(flag, PPas) == 0)
            flags += PPas_BIT;
        else if (strcmp(flag, IFut) == 0)
            flags += IFut_BIT;
        else if (strcmp(flag, CPre) == 0)
            flags += CPre_BIT;
        else if (strcmp(flag, Inf) == 0)
            flags += Inf_BIT;
        else if (strcmp(flag, InvGen) == 0)
            flags += InvGen_BIT;
        else if (strcmp(flag, InvPL) == 0)
            flags += InvPL_BIT;
    } while ((flag = strtok_r(NULL, "+", &saveptr1)));
    return flags;
}

// TODO : resolve the bug with multiple forms on the same word
t_dictionary extractFile(char *path)
{
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    char line[MAX_SIZE_LINE];
    int i = 0;
    t_dictionary dictionary;
    dictionary.nouns = create_tree();
    dictionary.adjectives = create_tree();
    dictionary.adverbs = create_tree();
    dictionary.verbs = create_tree();
    dictionary.pronouns = create_tree();
    dictionary.determinants = create_tree();
    while (fgets(line, MAX_SIZE_LINE, fp))
    {
        char **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            char *saveptr;
            char *type = strtok_r(extractedStrings[2], ":", &saveptr);
            if (strcmp(type, NOUN_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok_r(NULL, ":", &saveptr)))
                {
                    addInTree(dictionary.nouns, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, VERB_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok_r(NULL, ":", &saveptr)))
                {
                    addInTree(dictionary.verbs, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, ADJECTIVE_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok_r(NULL, ":", &saveptr)))
                {
                    addInTree(dictionary.adjectives, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, ADVERB_TYPE) == 0)
            {
                addInTree(dictionary.adverbs, extractedStrings[0], extractedStrings[1], 0);
            }
            else if (strcmp(type, PRONOUN_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok_r(NULL, ":", &saveptr)))
                {
                    addInTree(dictionary.pronouns, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, DETERMINANTS_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok_r(NULL, ":", &saveptr)))
                {
                    addInTree(dictionary.determinants, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
        }
        free(extractedStrings);
        i++;
    }
    printf("number of lines : %d\n", i);
    fclose(fp);
    return dictionary;
}

p_buffer createBuffer()
{
    p_buffer buffer = (p_buffer)malloc(sizeof(t_buffer));
    buffer->size = 0;
    buffer->first = NULL;
    buffer->last = NULL;
    return buffer;
}

void addToBuffer(p_buffer buffer, char *line)
{
    p_line entry = (p_line)malloc(sizeof(t_line));
    strcpy(entry->line, line);
    entry->next = NULL;
    entry->prev = buffer->last;
    if (buffer->size == 0)
    {
        buffer->first = entry;
        buffer->last = entry;
    }
    else
    {
        buffer->last->next = entry;
        buffer->last = entry;
    }
    buffer->size++;
}

void updateFile(char *path, t_inputWord word)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    char line[MAX_SIZE_LINE];
    p_buffer buffer = createBuffer();
    while (fgets(line, MAX_SIZE_LINE, fp))
    {
        addToBuffer(buffer, line);
    }
    fclose(fp);
    fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    p_line entry = buffer->first;
    int i = 0;
    bool inserted = false;
    while (entry != NULL && i < 300000)
    {
        i++;
        char **extractedStrings = extractWord(entry->line);
        if (strcmp(extractedStrings[0], word.word) == 0 && !inserted)
        {
            fprintf(fp, "%s\t%s\t%s:%s\n", extractedStrings[0], extractedStrings[1], extractedStrings[2], word.flags);
            entry = entry->next;
            inserted = true;
            continue;
        }
        else if (strcmp(extractedStrings[0], word.word) > 0 && !inserted)
        {
            fprintf(fp, "%s\t%s\t%s:%s\n", word.word, word.base, word.type, word.flags);
            inserted = true;
        }
        fprintf(fp, "%s\t%s\t%s\n", extractedStrings[0], extractedStrings[1], extractedStrings[2]);
        entry = entry->next;
    }
    fclose(fp);
    return;
}