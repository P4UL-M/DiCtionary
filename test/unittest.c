/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "string.h"
#include "../src/types/struct.h"
#include "../src/functions/dictionary.h"
#include "../src/functions/search.h"
#include "../src/functions/random.h"
#include "../src/functions/sentence.h"
#include "../src/menu/menu.h"

void displayTree(p_tree dico)
{
    printf("%sNODE '%p' with value %c\n", ANSI_COLOR_RED, dico, dico->value);
    printf("%s-> ponderation: %d\n", ANSI_COLOR_GREEN, dico->ponderation);
    printf("%sENUMERATING CHILD%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    for (p_child child = dico->children; child != NULL; child = child->next)
    {
        displayTree(child->node);
    }
    printf("%sEnd of node '%p'%s\n", ANSI_COLOR_BLUE, dico, ANSI_COLOR_RESET);
}

int checkExtract(t_dictionary dictionary, char *path)
{
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    char line[MAX_SIZE_LINE];
    while (fgets(line, MAX_SIZE_LINE, fp))
    {
        char **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            char *type = strtok(extractedStrings[2], ":");
            if (strcmp(type, NOUN_TYPE) == 0)
            {
                p_word word = getWord(dictionary.nouns, extractedStrings[0], true);
                if (word == NULL)
                {
                    printf("Error in noun %s\n", extractedStrings[0]);
                    return 1;
                }
                p_word baseWord = getWord(dictionary.nouns, extractedStrings[1], false);
                if (baseWord == NULL)
                {
                    printf("Error in noun %s\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (strcmp(type, VERB_TYPE) == 0)
            {
                p_word word = getWord(dictionary.verbs, extractedStrings[0], true);
                if (word == NULL)
                {
                    printf("Error in verb %s\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.verbs, extractedStrings[1], false);
                if (base == NULL)
                {
                    printf("Error in verb %s\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (strcmp(type, ADJECTIVE_TYPE) == 0)
            {
                p_word word = getWord(dictionary.adjectives, extractedStrings[0], true);
                if (word == NULL)
                {
                    printf("Error in adjective base %s\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.adjectives, extractedStrings[1], false);
                if (base == NULL)
                {
                    printf("Error in adjective base %s\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (strcmp(type, ADVERB_TYPE) == 0)
            {
                p_word word = getWord(dictionary.adverbs, extractedStrings[0], true);
                if (word == NULL)
                {
                    printf("Error in adverb base %s\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.adverbs, extractedStrings[1], false);
                if (base->base != word->base)
                {
                    printf("Error in adverb base %s\n", extractedStrings[1]);
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
    clock_t t;
    t = clock();
    t_dictionary dictionary = extractFile("data/dictionnaire.txt");
    buildPonderations(dictionary);
    printf("number of words: %d", dictionary.nouns->ponderation + dictionary.verbs->ponderation + dictionary.adjectives->ponderation + dictionary.adverbs->ponderation);
    printf("Time taken to extract the dictionary : %f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    for (int i = 0; i < 1000; i++)
    {
        generateSentence(dictionary, 3, true);
    }
    if (checkRandom(dictionary) == 0)
    {
        printf("Random words are correct\n");
    }
    if (checkExtract(dictionary, "data/dictionnaire.txt") == 0)
    {
        printf("Extracted file is correct\n");
    }
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}