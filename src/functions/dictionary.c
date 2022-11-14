/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <wchar.h>
#ifdef _WIN32
wchar_t *wcstok_s(wchar_t *str, const wchar_t *delim, wchar_t **ptr);
#define wcstok wcstok_s
#endif
#include "dictionary.h"
#include "search.h"
#include "../types/struct.h"
#include "../types/constants.h"

wchar_t **extractWord(wchar_t *source)
{
    source[wcscspn(source, L"\n")] = 0;
    wchar_t **saveptr = malloc(sizeof(wchar_t *));
    wchar_t **output = (wchar_t **)malloc(sizeof(wchar_t *) * 3);
    // separate the word, the base form and the type
    output[0] = wcstok(source, L"\t", saveptr);
    output[1] = wcstok(NULL, L"\t", saveptr);
    output[2] = wcstok(NULL, L"\t", saveptr);
    return output;
}

p_node addBaseInTree(p_tree node, wchar_t *word)
{
    for (int i = 0; i < wcslen(word); i++)
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

void addInTree(p_tree tree, wchar_t *word, wchar_t *base, int tag)
{
    p_node node = search(tree, base);
    if (node == NULL)
    {
        node = addBaseInTree(tree, base);
    }
    if (wcscmp(word, base) == 0)
    {
        tag += Main_BIT;
    }
    addForm(node, word, tag);
}

int countChar(wchar_t *word, wchar_t c)
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

unsigned int getFlags(wchar_t *tag)
{
    wchar_t *saveptr1;
    wchar_t *flag = wcstok(tag, L"+", &saveptr1);
    unsigned int flags = 0;
    do
    {
        if (wcscmp(flag, P1) == 0)
            flags += P1_BIT;
        else if (wcscmp(flag, P2) == 0)
            flags += P2_BIT;
        else if (wcscmp(flag, P3) == 0)
            flags += P3_BIT;
        else if (wcscmp(flag, Mas) == 0)
            flags += Mas_BIT;
        else if (wcscmp(flag, Fem) == 0)
            flags += Fem_BIT;
        else if (wcscmp(flag, PL) == 0)
            flags += PL_BIT;
        else if (wcscmp(flag, SG) == 0)
            flags += SG_BIT;
        else if (wcscmp(flag, IPre) == 0)
            flags += IPre_BIT;
        else if (wcscmp(flag, IImp) == 0)
            flags += IImp_BIT;
        else if (wcscmp(flag, SPre) == 0)
            flags += SPre_BIT;
        else if (wcscmp(flag, IPSim) == 0)
            flags += IPSim_BIT;
        else if (wcscmp(flag, PPre) == 0)
            flags += PPre_BIT;
        else if (wcscmp(flag, SImp) == 0)
            flags += SImp_BIT;
        else if (wcscmp(flag, PPas) == 0)
            flags += PPas_BIT;
        else if (wcscmp(flag, IFut) == 0)
            flags += IFut_BIT;
        else if (wcscmp(flag, CPre) == 0)
            flags += CPre_BIT;
        else if (wcscmp(flag, Inf) == 0)
            flags += Inf_BIT;
        else if (wcscmp(flag, InvGen) == 0)
            flags += InvGen_BIT;
        else if (wcscmp(flag, InvPL) == 0)
            flags += InvPL_BIT;
    } while ((flag = wcstok(NULL, L"+", &saveptr1)));
    return flags;
}

t_dictionary extractFile(char *path)
{
    FILE *fp;
    fp = fopen(path, "r,ccs=UNICODE");
    if (fp == NULL)
    {
        wprintf(L"Error opening file");
        exit(1);
    }
    wchar_t line[MAX_SIZE_LINE];
    int i = 0;
    t_dictionary dictionary;
    dictionary.nouns = create_tree();
    dictionary.adjectives = create_tree();
    dictionary.adverbs = create_tree();
    dictionary.verbs = create_tree();
    dictionary.pronouns = create_tree();
    dictionary.determinants = create_tree();
    while (fgetws(line, MAX_SIZE_LINE, fp))
    {
        wchar_t **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            wchar_t *saveptr;
            wchar_t *type = wcstok(extractedStrings[2], L":", &saveptr);
            if (wcscmp(type, NOUN_TYPE) == 0)
            {
                wchar_t *form = NULL;
                while ((form = wcstok(NULL, L":", &saveptr)))
                {
                    addInTree(dictionary.nouns, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (wcscmp(type, VERB_TYPE) == 0)
            {
                wchar_t *form = NULL;
                while ((form = wcstok(NULL, L":", &saveptr)))
                {
                    addInTree(dictionary.verbs, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (wcscmp(type, ADJECTIVE_TYPE) == 0)
            {
                wchar_t *form = NULL;
                while ((form = wcstok(NULL, L":", &saveptr)))
                {
                    addInTree(dictionary.adjectives, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (wcscmp(type, ADVERB_TYPE) == 0)
            {
                addInTree(dictionary.adverbs, extractedStrings[0], extractedStrings[1], 0);
            }
            else if (wcscmp(type, PRONOUN_TYPE) == 0)
            {
                wchar_t *form = NULL;
                while ((form = wcstok(NULL, L":", &saveptr)))
                {
                    addInTree(dictionary.pronouns, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (wcscmp(type, DETERMINANTS_TYPE) == 0)
            {
                wchar_t *form = NULL;
                while ((form = wcstok(NULL, L":", &saveptr)))
                {
                    addInTree(dictionary.determinants, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
        }
        free(extractedStrings);
        i++;
    }
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

void addToBuffer(p_buffer buffer, wchar_t *line)
{
    p_line entry = (p_line)malloc(sizeof(t_line));
    wcscpy(entry->line, line);
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
    FILE *fp = fopen(path, "r,ccs=UNICODE");
    if (fp == NULL)
    {
        wprintf(L"Error opening file");
        exit(1);
    }
    wchar_t line[MAX_SIZE_LINE];
    p_buffer buffer = createBuffer();
    while (fgetws(line, MAX_SIZE_LINE, fp))
    {
        addToBuffer(buffer, line);
    }
    fclose(fp);
    fp = fopen(path, "w,ccs=UNICODE");
    if (fp == NULL)
    {
        wprintf(L"Error opening file");
        exit(1);
    }
    p_line entry = buffer->first;
    int i = 0;
    bool inserted = false;
    while (entry != NULL && i < 300000)
    {
        i++;
        wchar_t **extractedStrings = extractWord(entry->line);
        if (wcscmp(extractedStrings[0], word.word) == 0 && !inserted)
        {
            fprintf(fp, "%ls\t%ls\t%ls:%ls\n", extractedStrings[0], extractedStrings[1], extractedStrings[2], word.flags);
            entry = entry->next;
            inserted = true;
            continue;
        }
        else if (wcscmp(extractedStrings[0], word.word) > 0 && !inserted)
        {
            fprintf(fp, "%ls\t%ls\t%ls:%ls\n", word.word, word.base, word.type, word.flags);
            inserted = true;
        }
        fprintf(fp, "%ls\t%ls\t%ls\n", extractedStrings[0], extractedStrings[1], extractedStrings[2]);
        entry = entry->next;
    }
    fclose(fp);
    return;
}