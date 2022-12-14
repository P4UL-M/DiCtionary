/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
#include "../types/struct.h"
#include "../types/pile.h"
#include "../types/constants.h"
#include "../functions/search.h"
#include "display.h"

void displayForm(t_form form)
// To print all declinaisons for the noun
{
    // Conjugaisons of the verbs:
    if ((form.tag & Inf_BIT) == Inf_BIT)
    {
        wprintf(L"present infinitive");
        return;
    }
    else if ((form.tag & PPas_BIT) == PPas_BIT)
        wprintf(L"past participle ");
    else if ((form.tag & PPre_BIT) == PPre_BIT)
        wprintf(L"present participle");
    else if ((form.tag & IImp_BIT) == IImp_BIT)
        wprintf(L"imperfect of the indicative at the ");
    else if ((form.tag & SPre_BIT) == SPre_BIT)
        wprintf(L"present of the subjonctive at the ");
    else if ((form.tag & IPSim_BIT) == IPSim_BIT)
        wprintf(L"simple past of the indicative at the ");
    else if ((form.tag & SImp_BIT) == SImp_BIT)
        wprintf(L"imperfect of the subjonctive at the ");
    else if ((form.tag & IFut_BIT) == IFut_BIT)
        wprintf(L"future of the indicative at the ");
    else if ((form.tag & CPre_BIT) == CPre_BIT)
        wprintf(L"present of the conditional at the ");
    else if ((form.tag & IPre_BIT) == IPre_BIT)
        wprintf(L"present of the indicative at the ");
    else if ((form.tag & ImPre_BIT) == ImPre_BIT)
        wprintf(L"present of the imperative at the ");

    // Person for the verbs:
    if ((form.tag & P1_BIT) == P1_BIT)
        wprintf(L"first person ");
    else if ((form.tag & P2_BIT) == P2_BIT)
        wprintf(L"second person ");
    else if ((form.tag & P3_BIT) == P3_BIT)
        wprintf(L"third person ");

    // Plural/Singular:
    if ((form.tag & InvPL_BIT) == InvPL_BIT)
        wprintf(L"invariable in number");
    else if ((form.tag & PL_BIT) == PL_BIT)
        wprintf(L"plural");
    else if ((form.tag & SG_BIT) == SG_BIT)
        wprintf(L"singular");

    // Masculine/Feminine
    if ((form.tag & InvGen_BIT) == InvGen_BIT)
        wprintf(L" invariable in gender");
    else if ((form.tag & Mas_BIT) == Mas_BIT)
        wprintf(L" masculine");
    else if ((form.tag & Fem_BIT) == Fem_BIT)
        wprintf(L" feminine");
}

void displayForms(t_word word, t_form form)
// To display all alternative forms for the word
{
    wchar_t *person[] = {L"Je", L"Tu", L"Il", L"Nous", L"Vous", L"Ils", L"Masculine Singular", L"Feminine Singular", L"Masculine Plural", L"Feminine Plural"};
    int perstag[] = {P1_BIT + SG_BIT, P2_BIT + SG_BIT, P3_BIT + SG_BIT, P1_BIT + PL_BIT, P2_BIT + PL_BIT, P3_BIT + PL_BIT, Mas_BIT + SG_BIT, Fem_BIT + SG_BIT, Mas_BIT + PL_BIT, Fem_BIT + PL_BIT};
    displayForm(form);
    if (form.word != word.base->word || form.tag != word.base->tag)
    {
        wprintf(L".\nIt comes from %ls%ls%ls, that is ", ANSI_COLOR_MAGENTA, word.base->word, ANSI_COLOR_RESET);
        displayForm(*word.base);
    }
    else
        wprintf(L".\nIt is the base form of the word");
    t_node temp = {
        .forms = word.forms,
    };
    if (temp.forms == NULL)
        return;
    wprintf(L".\nOther forms of the word are :\n");

#pragma region Verbs
    p_form inf = getFormByTag(temp, Inf_BIT);
    if (inf != NULL)
        wprintf(L"%ls>Infinitive:\n\t%ls%ls%ls\n", ANSI_COLOR_RED, ANSI_COLOR_RESET, inf->word, ANSI_COLOR_RESET);
    p_form ipre = getFormByTag(temp, IPre_BIT);
    p_form iimp = getFormByTag(temp, IImp_BIT);
    p_form ipas = getFormByTag(temp, IPSim_BIT);
    p_form ifut = getFormByTag(temp, IFut_BIT);
    p_form pers;
    if (ipre != NULL || iimp != NULL || ipas != NULL || ifut != NULL)
    {
        wprintf(L"%ls>Indicative:\n", ANSI_COLOR_RED);
        if (ipre != NULL)
        {
            wprintf(L"\tPresent:\n");
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByTag(temp, perstag[i] + IPre_BIT);
                wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
            }
        }
        if (iimp != NULL)
        {
            wprintf(L"\t%lsImperfect:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByTag(temp, perstag[i] + IImp_BIT);
                wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
            }
        }
        if (ipas != NULL)
        {
            wprintf(L"\t%lsSimple past:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByTag(temp, perstag[i] + IPSim_BIT);
                wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
            }
        }
        if (ifut != NULL)
        {
            wprintf(L"\t%lsFuture:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByTag(temp, perstag[i] + IFut_BIT);
                wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
            }
        }
    }
    p_form sPre = getFormByTag(temp, SPre_BIT);
    p_form sImp = getFormByTag(temp, SImp_BIT);
    if (sPre != NULL || sImp != NULL)
    {
        wprintf(L"%ls>Subjonctive:\n", ANSI_COLOR_RED);
        if (sPre != NULL)
        {
            wprintf(L"\tPresent:\n");
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByTag(temp, perstag[i] + SPre_BIT);
                wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
            }
        }
        if (sImp != NULL)
        {
            wprintf(L"\t%lsImperfect:\n", ANSI_COLOR_RED);
            for (int i = 0; i < 6; i++)
            {
                pers = getFormByTag(temp, perstag[i] + SImp_BIT);
                wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
            }
        }
    }
    p_form cpre = getFormByTag(temp, CPre_BIT);
    if (cpre != NULL)
    {
        wprintf(L"%ls>Conditional:\n", ANSI_COLOR_RED);
        wprintf(L"\tPresent:\n");
        for (int i = 0; i < 6; i++)
        {
            pers = getFormByTag(temp, perstag[i] + CPre_BIT);
            wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
        }
    }
    p_form imp = getFormByTag(temp, ImPre_BIT);
    if (imp != NULL)
    {
        wprintf(L"%ls>Imperative:\n", ANSI_COLOR_RED);
        wprintf(L"\tPresent:\n");
        for (int i = 0; i < 6; i++)
        {
            if ((i == 0) || (i == 2) || (i == 5))
                continue;
            pers = getFormByTag(temp, perstag[i] + ImPre_BIT);
            wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
        }
    }
    p_form pPre = getFormByTag(temp, PPre_BIT);
    p_form pPas = getFormByTag(temp, PPas_BIT);
    if (pPre != NULL || pPas != NULL)
    {
        wprintf(L"%ls>Participles:\n", ANSI_COLOR_RED);
        if (pPre != NULL)
        {
            wprintf(L"\tPresent:\n");
            pers = getFormByTag(temp, PPre_BIT);
            if ((pers->tag & Mas_BIT) == Mas_BIT || (pers->tag & Fem_BIT) == Fem_BIT)
            {
                for (int i = 6; i < 10; i++)
                {
                    pers = getFormByTag(temp, perstag[i] + PPre_BIT);
                    wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
                }
            }
            else
                wprintf(L"\t\t%ls%ls\n", ANSI_COLOR_RESET, pers->word);
        }
        if (pPas != NULL)
        {
            wprintf(L"\t%lsPast:\n", ANSI_COLOR_RED);
            pers = getFormByTag(temp, PPas_BIT);
            if ((pers->tag & Mas_BIT) == Mas_BIT || (pers->tag & Fem_BIT) == Fem_BIT)
            {
                for (int i = 6; i < 10; i++)
                {
                    pers = getFormByTag(temp, perstag[i] + PPas_BIT);
                    wprintf(L"\t\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, (pers != NULL) ? pers->word : L"undefined");
                }
            }
            else
                wprintf(L"\t\t%ls%ls\n", ANSI_COLOR_RESET, pers->word);
        }
    }
#pragma endregion

#pragma region Nouns
    p_form declin;
    int Nounsaid = 1;
    for (int i = 6; i < 10; i++)
    {
        declin = getFormByTag(temp, perstag[i]);
        if (declin != NULL)
        {
            if (((declin->tag & PPas_BIT) != PPas_BIT) && ((declin->tag & PPre_BIT) != PPre_BIT))
            {
                if (Nounsaid)
                {
                    wprintf(L"%ls\n>Forms:\n", ANSI_COLOR_RED);
                    Nounsaid = 0;
                }
                wprintf(L"\t%ls%ls:%ls %ls\n", ANSI_COLOR_CYAN, person[i], ANSI_COLOR_RESET, declin->word);
            }
        }
    }
#pragma endregion
}
