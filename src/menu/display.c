/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "../functions/search.h"
#include "display.h"

void displayForm(p_form form)
// To print all declinaisons for the noun
{
    // Conjugaisons of the verbs:
    if ((form->tag & Inf_BIT) == Inf_BIT)
    {
        printf("present infinitive\n");
        return;
    }
    else if ((form->tag & PPas_BIT) == PPas_BIT)
        printf("past participe ");
    else if ((form->tag & PPre_BIT) == PPre_BIT)
        printf("present participe\n");
    else if ((form->tag & IImp_BIT) == IImp_BIT)
        printf("imperfect of the indicative at the ");
    else if ((form->tag & SPre_BIT) == SPre_BIT)
        printf("present of the subjonctive at the ");
    else if ((form->tag & IPsimp_BIT) == IPsimp_BIT)
        printf("simple past of the indicative at the ");
    else if ((form->tag & SImp_BIT) == SImp_BIT)
        printf("imperfect of the subjonctive at the ");
    else if ((form->tag & IFut_BIT) == IFut_BIT)
        printf("future of the indicative at the ");
    else if ((form->tag & CPre_BIT) == CPre_BIT)
        printf("present of the conditional at the ");
    else if ((form->tag & IPre_BIT) == IPre_BIT)
        printf("present of the indicative at the ");

    // Person for the verbs:
    if ((form->tag & P1_BIT) == P1_BIT)
        printf("first person ");
    else if ((form->tag & P2_BIT) == P2_BIT)
        printf("second person ");
    else if ((form->tag & P3_BIT) == P3_BIT)
        printf("third person ");

    // Plural/Singular:
    if ((form->tag & PL_BIT) == PL_BIT)
        printf("plural");
    else if ((form->tag & SG_BIT) == SG_BIT)
        printf("singular");

    // Masculine/Feminine
    if ((form->tag & Mas_BIT) == Mas_BIT && !isVerb)
        printf(" masculine");
    else if ((form->tag & Fem_BIT) == Fem_BIT && !isVerb)
        printf(" feminine");
}

void displayForms(p_word word, p_form form, bool isVerb)
{
    displayForm(form, isVerb);
    p_form baseform = getForm(word, word->base);
    if (baseform != form)
    {
        printf("\nIt comes from %s, that is ", baseform->word);
        displayForm(baseform, isVerb);
    }
    p_form temp = word->forms->next;
    printf("\nIts alternative forms are :");
    while (temp != NULL)
    {
        if (temp != form)
        {
            printf("temp : %s\nform : %s\n", temp->word, form->word);
            printf("\n%s that is ");
            displayForm(temp, isVerb);
        }
        temp = temp->next;
    }
}
