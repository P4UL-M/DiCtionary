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

char *smoothSentence(char *sentence)
{
    char *output = sentence;
    // detect le, la, les, l' and l
    char *index = output;
    while ((index = strchr(index, 'l')) && (index == output || *(index - 1) == ' '))
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

void generateSentence(t_dictionary dico, int sentenceType, bool trueRandom)
{
    if (sentenceType == 1)
    {
        /*noun adj verb det noun*/
        p_word temp = getRandomWord(dico.nouns, trueRandom);
        p_form sentence[6];
        int subject_flags;
        do
        {
            sentence[1] = randomFormWithMask(temp, 0, 0);
        } while (sentence[1] == NULL);
        subject_flags = sentence[1]->tag & ~Main_BIT;
        if ((subject_flags & InvPL_BIT) == InvPL_BIT)
            subject_flags -= rand() % 2 ? PL_BIT : SG_BIT;
        if ((subject_flags & InvGen_BIT) == InvGen_BIT)
            subject_flags -= rand() % 2 ? Mas_BIT : Fem_BIT;
        do
        {
            sentence[2] = accords(getRandomWord(dico.adjectives, trueRandom), subject_flags);
        } while (sentence[2] == NULL);
        p_word mydet = getWord(dico.determinants, "le", false);
        do
        {
            sentence[0] = accords(mydet, subject_flags);
        } while (sentence[0] == NULL);
        int nb = (subject_flags & SG_BIT) == SG_BIT ? SG_BIT : PL_BIT;
        do
        {
            sentence[3] = randomFormWithMask(getRandomWord(dico.verbs, trueRandom), nb + P3_BIT, CPre_BIT);
        } while (sentence[3] == NULL);
        do
        {
            sentence[5] = randomFormWithMask(getRandomWord(dico.nouns, trueRandom), 0, 0);
        } while (sentence[5] == NULL);
        int object_flags = sentence[5]->tag & ~Main_BIT;
        if ((object_flags & InvPL_BIT) == InvPL_BIT)
            object_flags -= rand() % 2 ? PL_BIT : SG_BIT;
        if ((object_flags & InvGen_BIT) == InvGen_BIT)
            object_flags -= rand() % 2 ? Mas_BIT : Fem_BIT;
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
        free(output);
        return;
    }
    if (sentenceType == 2)
    {
        /*noun 'qui' verb verb noun adj*/
        p_word temp = getRandomWord(dico.nouns, trueRandom);
        p_form sentence[8];
        int subject_flags;
        do
        {
            sentence[1] = randomFormWithMask(temp, 0, 0);
        } while (sentence[1] == NULL);
        subject_flags = sentence[1]->tag & ~Main_BIT;
        if ((subject_flags & InvPL_BIT) == InvPL_BIT)
            subject_flags -= rand() % 2 ? PL_BIT : SG_BIT;
        if ((subject_flags & InvGen_BIT) == InvGen_BIT)
            subject_flags -= rand() % 2 ? Mas_BIT : Fem_BIT;
        t_form qui = {
            .word = "qui",
            .tag = 0,
            .next = NULL,
        };
        sentence[2] = &qui;
        p_word mydet = getWord(dico.determinants, "le", false);
        do
        {
            sentence[0] = accords(mydet, subject_flags);
        } while (sentence[0] == NULL);
        int nb = (subject_flags & SG_BIT) == SG_BIT ? SG_BIT : PL_BIT;
        do
        {
            sentence[3] = randomFormWithMask(getRandomWord(dico.verbs, trueRandom), nb + P3_BIT, CPre_BIT + SImp_BIT + SPre_BIT);
        } while (sentence[3] == NULL);
        do
        {
            sentence[4] = randomFormWithMask(getRandomWord(dico.verbs, trueRandom), nb + P3_BIT, CPre_BIT + SImp_BIT + SPre_BIT);
        } while (sentence[4] == NULL);
        do
        {
            sentence[6] = randomFormWithMask(getRandomWord(dico.nouns, trueRandom), 0, 0);
        } while (sentence[6] == NULL);
        int object_flags = sentence[6]->tag & ~Main_BIT;
        if ((object_flags & InvPL_BIT) == InvPL_BIT)
            object_flags -= rand() % 2 ? PL_BIT : SG_BIT;
        if ((object_flags & InvGen_BIT) == InvGen_BIT)
            object_flags -= rand() % 2 ? Mas_BIT : Fem_BIT;
        do
        {
            sentence[5] = accords(mydet, object_flags);
        } while (sentence[4] == NULL);
        do
        {
            sentence[7] = randomFormWithMask(getRandomWord(dico.adjectives, trueRandom), object_flags, 0);
        } while (sentence[7] == NULL);
        char *output = malloc(sizeof(char) * 100);
        for (int i = 0; i < 8; i++)
        {
            output = strcat(output, sentence[i]->word);
            output = strcat(output, " ");
        }
        output = strcat(output, ".");
        printf("%s\n", smoothSentence(output));
        free(output);
        return;
    }
    if (sentenceType == 3)
    {
        /* pro verb det noun past participe "que" subjonctif det noun*/
        p_form sentence[9];
        do
        {
            sentence[1] = randomFormWithMask(getRandomWord(dico.verbs, trueRandom), 0, CPre_BIT + SImp_BIT + SPre_BIT + Inf_BIT + PPas_BIT + PPre_BIT);
        } while (sentence[1] == NULL);
        int nb = (sentence[1]->tag & SG_BIT) == SG_BIT ? SG_BIT : PL_BIT;
        int person = (sentence[1]->tag & P1_BIT) == P1_BIT ? P1_BIT : (sentence[1]->tag & P2_BIT) == P2_BIT ? P2_BIT
                                                                                                            : P3_BIT;
        do
        {
            sentence[0] = randomFormWithMask(getRandomWord(dico.pronouns, trueRandom), nb + person, 0);
        } while (sentence[0] == NULL);
        do
        {
            sentence[3] = randomFormWithMask(getRandomWord(dico.nouns, trueRandom), 0, 0);
        } while (sentence[3] == NULL);
        int object_flags = sentence[3]->tag & ~Main_BIT;
        if ((object_flags & InvPL_BIT) == InvPL_BIT)
            object_flags -= rand() % 2 ? PL_BIT : SG_BIT;
        if ((object_flags & InvGen_BIT) == InvGen_BIT)
            object_flags -= rand() % 2 ? Mas_BIT : Fem_BIT;
        p_word mydet = getWord(dico.determinants, "le", false);
        do
        {
            sentence[2] = accords(mydet, object_flags);
        } while (sentence[2] == NULL);
        do
        {
            sentence[4] = randomFormWithMask(getRandomWord(dico.verbs, trueRandom), object_flags, 0);
        } while (sentence[4] == NULL);
        t_form que = {
            .word = "que",
            .tag = 0,
            .next = NULL,
        };
        sentence[5] = &que;
        do
        {
            sentence[6] = randomFormWithMask(getRandomWord(dico.verbs, trueRandom), P3_BIT, IPre_BIT + IFut_BIT + IImp_BIT + CPre_BIT + IPSim_BIT);
        } while (sentence[6] == NULL);
        nb = (sentence[6]->tag & SG_BIT) == SG_BIT ? SG_BIT : PL_BIT;
        do
        {
            sentence[8] = randomFormWithMask(getRandomWord(dico.nouns, trueRandom), 0, 0);
        } while (sentence[8] == NULL);
        object_flags = sentence[8]->tag & ~Main_BIT;
        if ((object_flags & InvPL_BIT) == InvPL_BIT)
            object_flags -= rand() % 2 ? PL_BIT : SG_BIT;
        if ((object_flags & InvGen_BIT) == InvGen_BIT)
            object_flags -= rand() % 2 ? Mas_BIT : Fem_BIT;
        do
        {
            sentence[7] = accords(mydet, object_flags);
        } while (sentence[7] == NULL);
        char *output = malloc(sizeof(char) * 100);
        for (int i = 0; i < 9; i++)
        {
            output = strcat(output, sentence[i]->word);
            output = strcat(output, " ");
        }
        output = strcat(output, ".");
        printf("%s\n", smoothSentence(output));
        free(output);
        return;
    }
    return;
}