/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/struct.h"
#include "../types/constants.h"
#include "display.h"

void displayForm(p_form form, int type)
// To print all declinaisons for the noun
{
    // Conjugaisons of the verbs:
    if ((form->tag & Inf_BIT) == Inf_BIT && type == 1)
    {
        printf("present infinitive\n");
        return;
    }
    else if ((form->tag & PPas_BIT) == PPas_BIT && type == 1)
    {
        printf("past participe\n");
    }
    else if ((form->tag & PPre_BIT) == PPre_BIT && type == 1)
    {
        printf("present participe\n");
    }
    else if ((form->tag & IImp_BIT) == IImp_BIT && type == 1)
        printf("imperfect of the indicative at the ");

    else if ((form->tag & SPre_BIT) == SPre_BIT && type == 1)
        printf("present of the subjonctive at the ");

    else if ((form->tag & IPsimp_BIT) == IPsimp_BIT && type == 1)
        printf("simple past of the indicative at the ");

    else if ((form->tag & SImp_BIT) == SImp_BIT && type == 1)
        printf("imperfect of the subjonctive at the ");

    else if ((form->tag & IFut_BIT) == IFut_BIT && type == 1)
        printf("future of the indicative at the ");

    else if ((form->tag & CPre_BIT) == CPre_BIT && type == 1)
        printf("present of the conditional at the ");

    else if ((form->tag & IPre_BIT) == IPre_BIT && type == 1)
        printf("present of the indicative at the ");

    // Person for the verbs:
    if ((form->tag & P1_BIT) == P1_BIT && type == 1)
        printf("first person ");

    else if ((form->tag & P2_BIT) == P2_BIT && type == 1)
        printf("second person ");

    else if ((form->tag & P3_BIT) == P3_BIT && type == 1)
        printf("third person");

    // Plural/Singular:
    if ((form->tag & PL_BIT) == PL_BIT)
        printf("plural");

    else
        printf("singular");

    // Masculine/Feminine
    if ((form->tag & Mas_BIT) == Mas_BIT && type == 2)
        printf(" masculine\n");
    else if (type == 2)
        printf(" feminine\n");
}
