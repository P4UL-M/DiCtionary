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
    return getFormByIndex(&temp, tag);
}

void generateSentence(int sentenceType, t_dictionary dico)
{
    if (sentenceType == 1)
    {
        /*noun adj verb noun*/
        p_word noun1 = getRandomWord(dico.nouns, 1);
        p_word verb1 = getRandomWord(dico.verbs, 1);
        p_word noun2 = getRandomWord(dico.nouns, 1);
        p_word adj1 = getRandomWord(dico.adjectives, 1);
        p_form verb = accords(verb1, noun1->forms->tag);
        p_form adj = accords(adj1, noun1->forms->tag);
        printf("%s %s %s %s", noun1->base->word, verb->word, adj->word, noun2->base->word);
        return;
    }
    if (sentenceType == 2)
    {
        /*noun 'qui' verb verb noun adj*/
        return;
    }
    if (sentenceType == 3)
    {
        /*¯\_(ツ)_/¯*/
        return;
    }
}