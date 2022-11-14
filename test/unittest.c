/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "wchar.h"
#include "../src/types/struct.h"
#include "../src/functions/dictionary.h"
#include "../src/functions/search.h"
#include "../src/functions/random.h"
#include "../src/functions/sentence.h"
#include "../src/menu/menu.h"
#include <locale.h>
#ifdef _WIN32
wchar_t *wcstok_s(wchar_t *str, const wchar_t *delim, wchar_t **ptr);
#define wcstok wcstok_s
#endif

void displayTree(p_tree dico)
{
    wprintf(L"%sNODE '%p' with value %c\n", ANSI_COLOR_RED, dico, dico->value);
    wprintf(L"%s-> ponderation: %d\n", ANSI_COLOR_GREEN, dico->ponderation);
    wprintf(L"%sENUMERATING CHILD%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    for (p_child child = dico->children; child != NULL; child = child->next)
    {
        displayTree(child->node);
    }
    wprintf(L"%sEnd of node '%p'%s\n", ANSI_COLOR_BLUE, dico, ANSI_COLOR_RESET);
}

int checkExtract(t_dictionary dictionary, char *path)
{
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        wprintf(L"Error opening file");
        exit(1);
    }
    wchar_t line[MAX_SIZE_LINE];
    while (fgetws(line, MAX_SIZE_LINE, fp))
    {
        wchar_t **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            wchar_t *saveptr;
            wchar_t *type = wcstok(extractedStrings[2], L":", &saveptr);
            if (wcscmp(type, NOUN_TYPE) == 0)
            {
                p_word word = getWord(dictionary.nouns, extractedStrings[0], true);
                if (word == NULL)
                {
                    wprintf(L"Error in noun %ls\n", extractedStrings[0]);
                    return 1;
                }
                p_word baseWord = getWord(dictionary.nouns, extractedStrings[1], false);
                if (baseWord == NULL)
                {
                    wprintf(L"Error in noun %ls\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (wcscmp(type, VERB_TYPE) == 0)
            {
                p_word word = getWord(dictionary.verbs, extractedStrings[0], true);
                if (word == NULL)
                {
                    wprintf(L"Error in verb %ls\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.verbs, extractedStrings[1], false);
                if (base == NULL)
                {
                    wprintf(L"Error in verb %ls\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (wcscmp(type, ADJECTIVE_TYPE) == 0)
            {
                p_word word = getWord(dictionary.adjectives, extractedStrings[0], true);
                if (word == NULL)
                {
                    wprintf(L"Error in adjective base %ls\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.adjectives, extractedStrings[1], false);
                if (base == NULL)
                {
                    wprintf(L"Error in adjective base %ls\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (wcscmp(type, ADVERB_TYPE) == 0)
            {
                p_word word = getWord(dictionary.adverbs, extractedStrings[0], true);
                if (word == NULL)
                {
                    wprintf(L"Error in adverb base %ls\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.adverbs, extractedStrings[1], false);
                if (base->base != word->base)
                {
                    wprintf(L"Error in adverb base %ls\n", extractedStrings[1]);
                    return 1;
                }
            }
            free(extractedStrings);
        }
    }
    fclose(fp);
    return 0;
}

int checkRandom(t_dictionary dictionary)
{
    for (int i = 0; i < 10000; i++)
    {
        p_word word = getRandomWord(dictionary.nouns, true);
        if (word == NULL)
        {
            return 1;
        }
    }
    for (int i = 0; i < 1000000; i++)
    {
        p_word word = getRandomWord(dictionary.verbs, true);
        if (word == NULL)
        {
            return 1;
        }
    }
    for (int i = 0; i < 1000000; i++)
    {
        p_word word = getRandomWord(dictionary.adjectives, true);
        if (word == NULL)
        {
            return 1;
        }
    }
    for (int i = 0; i < 1000000; i++)
    {
        p_word word = getRandomWord(dictionary.adverbs, true);
        if (word == NULL)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    srand(time(NULL));
    char *locale = setlocale(LC_ALL, "");
    clock_t t;
    t = clock();
    wchar_t texte[50] = L"Salut Gérard !";
    wprintf(L"%ls\n", texte);
    for (int i = 0; texte[i] != '\0'; i++)
    {
        wprintf(L"%d - ", texte[i]);
    }
    wscanf(L"%ls", texte);
    wprintf(L"%ls\n", texte);
    for (int i = 0; texte[i] != '\0'; i++)
    {
        wprintf(L"%d - ", texte[i]);
    }
    wprintf(L"\n");
    FILE *fp;
    fp = fopen("data/test.txt", "r,ccs=UNICODE");
    if (fp == NULL)
    {
        wprintf(L"Error opening file");
        exit(1);
    }
    wchar_t line[MAX_SIZE_LINE];
    while (fgetws(line, MAX_SIZE_LINE, fp))
    {
        wprintf(L"%ls\n", line);
        for (int i = 0; line[i] != '\0'; i++)
        {
            wprintf(L"%d - ", line[i]);
        }
    }

    return 0;
    t_dictionary dictionary = extractFile("data/dictionnaire.txt");
    buildPonderations(dictionary);
    wprintf(L"number of words: %d", dictionary.nouns->ponderation + dictionary.verbs->ponderation + dictionary.adjectives->ponderation + dictionary.adverbs->ponderation);
    wprintf(L"Time taken to extract the dictionary : %f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    for (int i = 0; i < 1000; i++)
    {
        generateSentence(dictionary, 3, true);
    }
    if (checkRandom(dictionary) == 0)
    {
        wprintf(L"Random words are correct\n");
    }
    if (checkExtract(dictionary, "data/dictionnaire.txt") == 0)
    {
        wprintf(L"Extracted file is correct\n");
    }
    wprintf(L"time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}