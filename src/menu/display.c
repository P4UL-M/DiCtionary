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

void displayForm(t_form form)
// To print all declinaisons for the noun
{
    // Conjugaisons of the verbs:
    if ((form.tag & Inf_BIT) == Inf_BIT)
    {
        printf("present infinitive");
        return;
    }
    else if ((form.tag & PPas_BIT) == PPas_BIT)
        printf("past participle ");
    else if ((form.tag & PPre_BIT) == PPre_BIT)
        printf("present participle");
    else if ((form.tag & IImp_BIT) == IImp_BIT)
        printf("imperfect of the indicative at the ");
    else if ((form.tag & SPre_BIT) == SPre_BIT)
        printf("present of the subjonctive at the ");
    else if ((form.tag & IPSim_BIT) == IPSim_BIT)
        printf("simple past of the indicative at the ");
    else if ((form.tag & SImp_BIT) == SImp_BIT)
        printf("imperfect of the subjonctive at the ");
    else if ((form.tag & IFut_BIT) == IFut_BIT)
        printf("future of the indicative at the ");
    else if ((form.tag & CPre_BIT) == CPre_BIT)
        printf("present of the conditional at the ");
    else if ((form.tag & IPre_BIT) == IPre_BIT)
        printf("present of the indicative at the ");

    // Person for the verbs:
    if ((form.tag & P1_BIT) == P1_BIT)
        printf("first person ");
    else if ((form.tag & P2_BIT) == P2_BIT)
        printf("second person ");
    else if ((form.tag & P3_BIT) == P3_BIT)
        printf("third person ");

    // Plural/Singular:
    if ((form.tag & InvPL_BIT) == InvPL_BIT)
        printf(" invariable in number");
    else if ((form.tag & PL_BIT) == PL_BIT)
        printf("plural");
    else if ((form.tag & SG_BIT) == SG_BIT)
        printf("singular");

    // Masculine/Feminine
    if ((form.tag & InvGen_BIT) == InvGen_BIT)
        printf(" invariable in gender");
    else if ((form.tag & Mas_BIT) == Mas_BIT)
        printf(" masculine");
    else if ((form.tag & Fem_BIT) == Fem_BIT)
        printf(" feminine");
}

void displayForms(t_word word, t_form form)
{
    char *person[] = {"Je", "Tu", "Il", "Nous", "Vous", "Ils", "Masculine Singular", "Feminine Singular", "Masculine Plural", "Feminine Plural"};
    int perstag[] = {P1_BIT + SG_BIT, P2_BIT + SG_BIT, P3_BIT + SG_BIT, P1_BIT + PL_BIT, P2_BIT + PL_BIT, P3_BIT + PL_BIT, Mas_BIT + SG_BIT, Fem_BIT + SG_BIT, Mas_BIT + PL_BIT, Fem_BIT + PL_BIT};
    displayForm(form);
    if (form.word != word.base->word || form.tag != word.base->tag)
    {
        printf("\nIt comes from %s%s%s, that is ", ANSI_COLOR_MAGENTA, word.base->word, ANSI_COLOR_RESET);
        displayForm(*word.base);
    }
    else
        printf("\nIt is the base form of the word");
    t_node temp = {
        .forms = word.forms,
    };

#pragma region Verbs
    p_form inf = getFormByIndex(temp, Inf_BIT);
    if (inf != NULL)
        printf("%s\n>Infinitive:\n\t%s%s%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, inf->word, ANSI_COLOR_RESET);
    p_form ipre = getFormByIndex(temp, IPre_BIT);
    p_form iimp = getFormByIndex(temp, IImp_BIT);
    p_form ipas = getFormByIndex(temp, IPSim_BIT);
    p_form ifut = getFormByIndex(temp, IFut_BIT);
    p_form pers;
    if (ipre != NULL || iimp != NULL || ipas != NULL || ifut != NULL)
    {
        printf("%s>Indicative:\n", ANSI_COLOR_RED);
        if (ipre != NULL)
        {
            printf("\tPresent:\n");
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByIndex(temp, perstag[i] + IPre_BIT);
                printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
            }
        }
        if (iimp != NULL)
        {
            printf("\t%sImperfect:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByIndex(temp, perstag[i] + IImp_BIT);
                printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
            }
        }
        if (ipas != NULL)
        {
            printf("\t%sSimple past:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByIndex(temp, perstag[i] + IPSim_BIT);
                printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
            }
        }
        if (ifut != NULL)
        {
            printf("\t%sFuture:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByIndex(temp, perstag[i] + IFut_BIT);
                printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
            }
        }
    }
    p_form sPre = getFormByIndex(temp, SPre_BIT);
    p_form sImp = getFormByIndex(temp, SImp_BIT);
    if (sPre != NULL || sImp != NULL)
    {
        printf("%s>Subjonctive:\n", ANSI_COLOR_RED);
        if (sPre != NULL)
        {
            printf("\tPresent:\n");
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByIndex(temp, perstag[i] + SPre_BIT);
                printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
            }
        }
        if (sImp != NULL)
        {
            printf("\t%sImperfect:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByIndex(temp, perstag[i] + SImp_BIT);
                printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
            }
        }
    }
    p_form cpre = getFormByIndex(temp, CPre_BIT);
    if (cpre != NULL)
    {
        printf("%s>Conditional:\n", ANSI_COLOR_RED);
        printf("\tPresent:\n");
        for (int i = 0; i < 6; i++)
        {
            pers = getFormByIndex(temp, perstag[i] + CPre_BIT);
            printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
        }
    }
    p_form pPre = getFormByIndex(temp, PPre_BIT);
    p_form pPas = getFormByIndex(temp, PPas_BIT);
    if (pPre != NULL || pPas != NULL)
    {
        printf("%s>Participles:\n", ANSI_COLOR_RED);
        if (pPre != NULL)
        {
            printf("\tPresent:\n");
            pers = getFormByIndex(temp, PPre_BIT);
            if ((pers->tag & Mas_BIT) == Mas_BIT || (pers->tag & Fem_BIT) == Fem_BIT)
            {
                for (int i = 6; i < 10; i++)
                {
                    pers = getFormByIndex(temp, perstag[i] + PPre_BIT);
                    printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
                }
            }
            else
                printf("\t\t%s%s\n", ANSI_COLOR_RESET, pers->word);
        }
        if (pPas != NULL)
        {
            printf("\t%sPast:\n", ANSI_COLOR_RED);
            pers = getFormByIndex(temp, PPas_BIT);
            if ((pers->tag & Mas_BIT) == Mas_BIT || (pers->tag & Fem_BIT) == Fem_BIT)
            {
                for (int i = 6; i < 10; i++)
                {
                    pers = getFormByIndex(temp, perstag[i] + PPas_BIT);
                    printf("\t\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : "undefined");
                }
            }
            else
                printf("\t\t%s%s\n", ANSI_COLOR_RESET, pers->word);
        }
    }
#pragma endregion

#pragma region Nouns
    p_form declin;
    int Nounsaid = 1;
    for (int i = 6; i < 10; i++)
    {
        declin = getFormByIndex(temp, perstag[i]);
        if (declin != NULL)
        {
            if (((declin->tag & PPas_BIT) != PPas_BIT) && ((declin->tag & PPre_BIT) != PPre_BIT))
            {
                if (Nounsaid)
                {
                    printf("%s\n>Forms:\n", ANSI_COLOR_RED);
                    Nounsaid = 0;
                }
                printf("\n%s>Noun:\n", ANSI_COLOR_RED);
                printf("\t%s%s:%s %s\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, declin->word);
            }
        }
    }
#pragma endregion
}
