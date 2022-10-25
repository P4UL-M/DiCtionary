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

void addBaseInTree(p_tree tree, char *word)
{
    p_node node = get_child_from_tree(tree, word[0]);
    if (node == NULL)
    {
        add_child_to_tree(tree, word[0]);
        node = get_child_from_tree(tree, word[0]);
    }
    for (int i = 1; i < strlen(word); i++)
    {
        p_node child = get_child(node, word[i]);
        if (child == NULL)
        {
            add_child(node, word[i]);
            node = get_child(node, word[i]);
        }
        else
        {
            node = child;
        }
    }
}

void addInTree(p_tree tree, char *word, char *base, char *tag)
{
    if (tag == NULL && search(tree, word) == NULL)
    {
        addBaseInTree(tree, word);
    }
    else
    {
        p_node node = search(tree, base);
        if (node == NULL)
        {
            addBaseInTree(tree, base);
            node = search(tree, base);
        }
        add_form(node, word, tag);
    }
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
        // printf("line %d: %s", i, line);
        char **extractedStrings = extractWord(line);
        if (extractedStrings != NULL)
        {
            char *type = strtok(extractedStrings[2], ":");
            if (strcmp(type, NOUN_TYPE) == 0)
            {
                // printf("noun -> '%s'\n", type);
                char *form = NULL;
                while (form = strtok(NULL, ":"))
                {
                    // printf("form : '%s' - word : '%s' - base : '%s'\n", form, extractedStrings[0], extractedStrings[1]);
                    addInTree(dictionary.nouns, extractedStrings[0], extractedStrings[1], form);
                }
            }
            else if (strcmp(type, VERB_TYPE) == 0)
            {
                // printf("Verb\n");
            }
            else if (strcmp(type, ADJECTIVE_TYPE) == 0)
            {
                // printf("Adjective\n");
            }
            else if (strcmp(type, ADVERB_TYPE) == 0)
            {
                // printf("Adverb\n");
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