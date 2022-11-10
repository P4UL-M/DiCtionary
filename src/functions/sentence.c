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

p_form accords(p_word word, int tag)
{
    t_node temp = {
        .forms = word->forms,
    };
    return getFormByIndex(temp, tag);
}

// TODO faire func smoth sentence which correct problem such has le arrosoir -> l'arrosoir

p_form randomFormWithMask(p_word word, int mask, int antimask)
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
        p_form sentence[4];
        int subject_flags;
        do
        {
            sentence[0] = randomFormWithMask(temp, 0, 0);
        } while (sentence[0] == NULL);
        subject_flags = sentence[0]->tag;
        do
        {
            sentence[1] = accords(getRandomWord(dico.adjectives, true), subject_flags);
        } while (sentence[1] == NULL);
        int nb = 0;
        nb += subject_flags & (SG_BIT);
        nb += subject_flags & (PL_BIT);
        nb += subject_flags & (InvPL_BIT) ? (SG_BIT) : 0;
        do
        {
            sentence[2] = randomFormWithMask(getRandomWord(dico.verbs, true), nb + P3_BIT, CPre_BIT);
        } while (sentence[2] == NULL);
        do
        {
            temp = getRandomWord(dico.nouns, true);
            sentence[3] = randomFormWithMask(temp, 0, 0);
        } while (sentence[3] == NULL);
        for (int i = 0; i < 4; i++)
        {
            printf("%s ", sentence[i]->word);
        }
        printf(".\n");
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