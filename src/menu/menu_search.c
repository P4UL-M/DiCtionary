/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/struct.h"
#include "../types/constants.h"

void displayResult(p_form result)
// To print all declinaisons for the noun
{
    // Conjugaisons of the verbs:
    if (result->tag & Inf_BIT == Inf_BIT)
    {
        printf("present infinitive\n");
        return;
    }
    else if (result->tag & PPas_BIT == PPas_BIT)
    {
        printf("past participe\n");
    }
    else if (result->tag & PPre_BIT == PPre_BIT)
    {
        printf("present participe\n");
    }
    else if (result->tag & IImp_BIT == IImp_BIT)
        printf("imperfect of the indicative at the ");

    else if (result->tag & SPre_BIT == SPre_BIT)
        printf("present of the subjonctive at the ");

    else if (result->tag & IPsimp_BIT == IPsimp_BIT)
        printf("simple past of the indicative at the ");

    else if (result->tag & SImp_BIT == SImp_BIT)
        printf("imperfect of the subjonctive at the ");

    else if (result->tag & IFut_BIT == IFut_BIT)
        printf("future of the indicative at the ");

    else if (result->tag & CPre_BIT == CPre_BIT)
        printf("present of the conditional at the ");

    else if (result->tag & IPre_BIT)
        printf("present of the indicative at the ");

    // Person for the verbs:
    if (result->tag & P1_BIT == P1_BIT)
        printf("first person ");

    else if (result->tag & P2_BIT == P2_BIT)
        printf("second person ");

    else if (result->tag & P3_BIT == P3_BIT)
        printf("third person");

    // Plural/Singular:
    if (result->tag & PL_BIT == PL_BIT)
        printf("plural");

    else
        printf("singular");

    // Masculine/Feminine
    if (result->tag & Mas_BIT == Mas_BIT)
        printf(" masculine\n");
    else
        printf(" feminine\n");
}
