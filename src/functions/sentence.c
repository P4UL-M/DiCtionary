#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/random.h"
#include "../functions/dictionary.h"
#include "../functions/search.h"
#include "../menu/display.h"

p_form accords(p_word word, unsigned int tag)
{
    t_node temp = {
        .forms = word->forms,
    };
    return getFormByIndex(temp, tag);
}

// TODO faire func smoth sentence which correct problem such has le arrosoir -> l'arrosoir
char *smoothSentence(char *sentence)
{
    char *output = (char *)malloc(sizeof(char) * strlen(sentence));
    strcpy(output, sentence);
    // detect le, la, les, l' and l
    char *index = output;
    while ((index = strchr(index, 'l')))
    {
        if (strpbrk(index, "ae") == index + 1 && strchr(index, ' ') == index + 2)
        {
            char *next = index + 3;
            if (strpbrk(next, "aeiouy") == next)
            {
                *(index + 1) = '\'';
                memmove(index + 2, index + 3, strlen(index + 3) + 1);
            }
        }
        index += 3;
    }
    // remove space before ponctuation
    index = output;
    while ((index = strchr(index, ' ')))
    {
        if (strchr(index, '.') == index + 1)
        {
            memmove(index, index + 1, strlen(index));
        }
        index++;
    }
    // make first letter uppercase
    *output = *output - 32;
    return output;
}

p_form randomFormWithMask(p_word word, unsigned int mask, unsigned int antimask)
{
    p_form form = word->forms;
    int count = 0;
    p_form *forms = malloc(sizeof(p_form));
    while (form != NULL)
    {
        if ((form->tag & mask) == mask && (antimask == 0 || (form->tag & antimask) == 0))
        {

            count++;
            forms = realloc(forms, count * sizeof(p_form));
            forms[count - 1] = form;
        }
        form = form->next;
    }
    if (count == 0)
    {
        free(forms);
        return NULL;
    }
    int index = rand() / (float)RAND_MAX * (count - 1);
    p_form result = forms[index];
    free(forms);
    return result;
}

void generateSentence(int sentenceType, t_dictionary dico)
{
    if (sentenceType == 1)
    {
        /*noun adj verb det noun*/
        p_word temp = getRandomWord(dico.nouns, true);
        p_form sentence[6];
        int subject_flags;
        do
        {
            sentence[1] = randomFormWithMask(temp, 0, 0);
        } while (sentence[1] == NULL);
        subject_flags = sentence[1]->tag & ~Main_BIT;
        do
        {
            sentence[2] = accords(getRandomWord(dico.adjectives, true), subject_flags);
        } while (sentence[2] == NULL);
        p_word mydet = getWord(dico.determinants, "le", false);
        do
        {
            sentence[0] = accords(mydet, subject_flags);
        } while (sentence[0] == NULL);
        int nb = (subject_flags & SG_BIT) == SG_BIT ? SG_BIT : PL_BIT;
        do
        {
            sentence[3] = randomFormWithMask(getRandomWord(dico.verbs, true), nb + P3_BIT, CPre_BIT);
        } while (sentence[3] == NULL);
        do
        {
            temp = getRandomWord(dico.nouns, true);
            sentence[5] = randomFormWithMask(temp, 0, 0);
        } while (sentence[5] == NULL);
        int object_flags = sentence[5]->tag & ~Main_BIT;
        do
        {
            sentence[4] = accords(mydet, object_flags);
        } while (sentence[4] == NULL);
        char *output = malloc(sizeof(char) * 100);
        for (int i = 0; i < 6; i++)
        {
            output = strcat(output, sentence[i]->word);
            output = strcat(output, " ");
        }
        output = strcat(output, ".");
        printf("%s\n", smoothSentence(output));
        return;
    }
    if (sentenceType == 2)
    {
        /*noun 'qui' verb verb noun adj*/
        return;
    }
    if (sentenceType == 3)
    {
        /* pro noun adj verb det noun adj*/
        return;
    }
}