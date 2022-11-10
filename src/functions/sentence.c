#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/random.h"
#include "../functions/dictionary.h"

// TODO : rewrite this function
p_form according(p_tree tree, int form)
{
    p_node current_node = findRandom(tree);
    p_form current_form = current_node->forms;
    while (current_form->tag != form)
    {
        if (current_form->next == NULL)
        {
            current_node = findRandom(tree);
            current_form = current_node->forms;
        }
        else
        {
            current_form = current_form->next;
        }
    }
    return current_form;
}

void generateSentence(int sentenceType, t_dictionary dico)
{
    if (sentenceType == 1)
    {
        /*noun adj verb noun*/

        p_word noun1 = getRandomWord(dico.nouns, 1);
        p_form verb = according(dico.verbs, noun1->forms->tag);
        p_form adj = according(dico.adjectives, noun1->forms->tag);
        p_word noun2 = getRandomWord(dico.nouns, 1);
        printf("%s %s %s %s", noun1->base, verb->word, adj->word, noun2->base);
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