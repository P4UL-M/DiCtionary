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

int randomTime()
{
    int times[] = {IPre_BIT, IImp_BIT, SPre_BIT, IPSim_BIT, SImp_BIT, IFut_BIT, CPre_BIT};
    int index = rand() / (float)RAND_MAX * 7;
    return times[index];
}

int randomPerson()
{
    int persons[] = {P1_BIT, P2_BIT, P3_BIT};
    int index = rand() / (float)RAND_MAX * 3;
    return persons[index];
}

int randomGender()
{
    int persones[] = {
        Mas_BIT + PL_BIT,
        Fem_BIT + PL_BIT,
        Mas_BIT + SG_BIT,
        Fem_BIT + SG_BIT,
    };
    int index = rand() / (float)RAND_MAX * 4;
    return persones[index];
}

void generateSentence(int sentenceType, t_dictionary dico)
{
    if (sentenceType == 1)
    {
        /*noun adj verb noun*/
        p_word word1;
        p_word word2;
        p_word word3;
        p_word word4;
        p_form sentence[4];
        int subject_flags;
        do
        {
            subject_flags = randomGender();
            word1 = getRandomWord(dico.nouns, true);
            word2 = getRandomWord(dico.adjectives, true);
            sentence[0] = accords(word1, subject_flags);
            sentence[1] = accords(word2, subject_flags);
        } while (sentence[1] == NULL || sentence[0] == NULL);
        printf("%s %s\n", sentence[0]->word, sentence[1]->word);
        int nb = subject_flags & PL_BIT + subject_flags & SG_BIT;
        do
        {
            sentence[2] = accords(getRandomWord(dico.verbs, true), P3_BIT + nb + randomTime());
        } while (sentence[2] == NULL);
        do
        {
            sentence[3] = accords(getRandomWord(dico.nouns, true), randomGender());
        } while (sentence[3] == NULL);
        for (int i = 0; i < 4; i++)
        {
            printf("word %d :%s\n", i, sentence[i]->word);
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