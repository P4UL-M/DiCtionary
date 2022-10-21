/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

char **extractWord(char *source)
{
    source[strcspn(source, "\n")] = 0;
    char **output = malloc(sizeof(char *) * 3);
    // separate the word, the base form and the type
    output[0] = strtok(source, "\t");
    output[1] = strtok(NULL, "\t");
    output[2] = strtok(NULL, "\t");
    return output;
}

void addToTree(char *declined_noun, char *base, char *declinaison, p_tree_noun tree)
{
}

void extractFile(char *path, p_tree_noun tree)
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

    while (fgets(line, MAX_SIZE_LINE, fp))
    {
        char **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            char *type = strtok(extractedStrings[2], ":");
            // if (strcmp(type, NOUN_TYPE))
            // {
            //     printf("Noun\n");
            // }
            // if (strcmp(type, VERB_TYPE))
            // {
            //     printf("Verb\n");
            // }
            // if (strcmp(type, ADJECTIVE_TYPE))
            // {
            //     printf("Adjective\n");
            // }
            // if (strcmp(type, ADVERB_TYPE))
            // {
            //     printf("Adverb\n");
            // }
            // else
            // {
            //     printf("Unknown type : %s, [%s,%s,%s,%s]\n", type, NOUN_TYPE, VERB_TYPE, ADJECTIVE_TYPE, ADVERB_TYPE);
            // }
        }
        free(extractedStrings);
        i++;
    }
    printf("number of lines : %d\n", i);
}