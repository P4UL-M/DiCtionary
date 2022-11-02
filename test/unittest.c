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
#include "../src/menu/menu.h"

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
                p_word base = getWord(dictionary.nouns, extractedStrings[1], false);
                if (base == NULL)
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
                    printf("Error in adjective %s\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.adjectives, extractedStrings[1], false);
                if (base == NULL)
                {
                    printf("Error in adjective %s\n", extractedStrings[1]);
                    return 1;
                }
            }
            else if (strcmp(type, ADVERB_TYPE) == 0)
            {
                p_word word = getWord(dictionary.adverbs, extractedStrings[0], true);
                if (word == NULL)
                {
                    printf("Error in adverb %s\n", extractedStrings[0]);
                    return 1;
                }
                p_word base = getWord(dictionary.adverbs, extractedStrings[1], false);
                if (base == NULL)
                {
                    printf("Error in adverb %s", extractedStrings[1]);
                    return 1;
                }
            }
            free(extractedStrings);
        }
    }
    fclose(fp);
    return 0;
}

int main()
{
    clock_t t;
    t = clock();
    t_dictionary dictionary = extractFile("data/dictionnaire.txt");
    printf("Time taken to extract the dictionary : %f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    if (checkExtract(dictionary, "data/dictionnaire.txt") == 0)
    {
        printf("Extracted file is correct\n");
    }
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}