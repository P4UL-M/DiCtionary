/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions in order to extract text from the dictionary*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "search.h"
#include "../types/struct.h"
#include "../types/constants.h"

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

int getFlags(char *tag)
{
    char *flag = strtok(tag, "+");
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
        else if (strcmp(flag, IPsimp) == 0)
            flags += IPsimp_BIT;
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
    } while ((flag = strtok(NULL, "+")));
    return flags;
}

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
    while (fgets(line, MAX_SIZE_LINE, fp))
    {
        char **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            char *type = strtok(extractedStrings[2], ":");
            if (strcmp(type, NOUN_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok(NULL, ":")))
                {
                    addInTree(dictionary.nouns, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, VERB_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok(NULL, ":")))
                {
                    addInTree(dictionary.verbs, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, ADJECTIVE_TYPE) == 0)
            {
                char *form = NULL;
                while ((form = strtok(NULL, ":")))
                {
                    addInTree(dictionary.adjectives, extractedStrings[0], extractedStrings[1], getFlags(form));
                }
            }
            else if (strcmp(type, ADVERB_TYPE) == 0)
            {
                addInTree(dictionary.adverbs, extractedStrings[0], extractedStrings[1], 0);
            }
            else
            {
                // printf("Unknown type : %s, [%d,%d,%d,%d]\n", type, strcmp(type, NOUN_TYPE), strcmp(type, VERB_TYPE), strcmp(type, ADJECTIVE_TYPE), strcmp(type, ADVERB_TYPE));
            }
        }
        free(extractedStrings);
        i++;
    }
    printf("number of lines : %d\n", i);
    fclose(fp);
    return dictionary;
}