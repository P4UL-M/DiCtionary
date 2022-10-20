#include <stdio.h>
#include <stdlib.h>
#include <regex.h> // for regular expressions
#include <string.h>

#include "dictionary.h"
#include "../types/nouns.h"

regex_t compileRegex()
{
    regex_t regex;
    if (regcomp(&regex, NOUN_REGEX, 0) != 0)
        printf("regcomp error\n");
    return regex;
}

char **extractWord(regex_t regex, char *source)
{
    size_t nmatch = 4;
    regmatch_t pmatch[nmatch];
    char **output = malloc(sizeof(char *) * (nmatch - 1));
    if (!regexec(&regex, source, nmatch, pmatch, 0))
    {
        for (unsigned int i = 1; i < nmatch; i++)
        {
            if (pmatch[i].rm_so == (size_t)-1)
                break; // No more groups

            char sourceCopy[strlen(source) + 1];
            strcpy(sourceCopy, source);
            sourceCopy[pmatch[i].rm_eo] = 0;
            output[i - 1] = sourceCopy + pmatch[i].rm_so;
        }
    }
    else
    {
        // printf("No match\n");
        return NULL;
    }
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

    regex_t regex = compileRegex();

    while (fgets(line, MAX_SIZE_LINE, fp) != NULL && i < NB_LINES)
    {
        // printf("%d |%s", ++i, line);
        char **extractedStrings = extractWord(regex, line);
        if (extractedStrings != NULL)
        {
            // printf("%s\t%s\t%s", extractedStrings[0], extractedStrings[1], extractedStrings[2]);
        }
        // printf("\n");
        free(extractedStrings);
        i++;
    }
    regfree(&regex);
}