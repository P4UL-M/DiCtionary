/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the menu*/
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "../types/adverbs.h"
#include "../types/nouns.h"
#include "../types/verbs.h"
#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#define sleep Sleep
#else
#include <unistd.h>
#define CLEAR "clear"
#endif
#define ANSI_COLOR_RED "\x1b[0m\x1b[31;4m"
#define ANSI_COLOR_GREEN "\x1b[0m\x1b[32;1;3m"
#define ANSI_COLOR_YELLOW "\x1b[0m\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[0m\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[0m\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[0m\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_BACKGROUND_WHITE "\x1b[0m\x1b[39;1m\e[47m\e[K"

void menu()
// Function that contains the main menu
{
    int action;
    system(CLEAR);
    printf("%s\tWelcome in the DiCtionary\t\n\n", ANSI_BACKGROUND_WHITE);
    do
    {
        printf("%sDo you want to:\n", ANSI_COLOR_GREEN);
        printf("%s1.%s Search for a word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf("%s2.%s Generate a random sentence?\n(Type 1 or 2)\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf(ANSI_COLOR_RESET);
        printf("\n>");
        scanf("%d", &action);
        fflush(stdin);
    } while (action < 1 || action > 2);
    if (action == 1)
    {
        search();
    }
    else
    {
        generate_sentence();
    }
    return;
}

void search()
// Function to launch the search of a word
{
    char searching[50];
    system(CLEAR);
    printf("%s\tWelcome in the DiCtionary\t\n\n", ANSI_BACKGROUND_WHITE);
    printf("%sEnter the word you want to search:\n", ANSI_COLOR_GREEN);
    printf(ANSI_COLOR_RESET);
    printf("\n>");
    scanf("%49s", &searching);
    p_version_noun result_noun = searchnoun(NounDictionary, searching);
    if (result_noun != NULL)
    {
        printf("%s is a noun that is ", result_noun->word);
        return;
    }
    p_version_adj result_adj = searchadj(AdjDictionary, searching);
    if (result_adj != NULL)
    {
        printf("%s is an adjectif that is ", result_adj->word);
        return;
    }
    p_version_noun result_verb = searchverb(VerbDictionary, searching);
    if (result_verb != NULL)
    {
        return;
    }
    p_node_adv result_adv = searchadv(AdvDictionary, searching);
    {
        printf("%s is an adverb\n");
        return;
    }
    printf("%s doesn't appear in the DiCtionary", searching);
    return;
}

void generate_sentence()
// Function to generate a random sentence
{
    printf("World\n");
}

void waitKey()
// Function to wait for the users in resolution
{
    fflush(stdin);
    printf("Press a key to continue...\n");
    sleep(1);
    while (1)
    {
        if (getchar())
        {
            fflush(stdin);
            break;
        }
    }
}

void printdeclinaison(t_forme_noun forme)
{
    switch (forme)
    {
    case Mas_SG:
        printf("singular masculine");
        break;
    case Mas_PL:
        printf("plural masculine");
        break;
    case Fem_SG:
        printf("singular feminine");
        break;
    case Fem_PL:
        printf("plural feminine");
        break;
    default:
        printf("all we know");
        break;
    }
}

void printversionnoun(p_version_noun vers)
{
    printdeclinaison(vers->forme);
    if (vers->declinaisons == NULL)
    {
        printf("\nIt has no other form\n");
        return;
    }
    printf("\nIts derivatives are :\n");
    for (int i = 0; i < sizeof(vers->declinaisons) / sizeof(t_declinaison_noun); i++)
    {
        printf("%s that is ", vers->declinaisons[i].word);
        printdeclinaison(vers->declinaisons[i].forme);
        printf("\n");
    }
}

void printperson(t_personne pers)
{
    switch (pers)
    {
    case SG_P1:
        printf("first person singular");
        break;
    case SG_P2:
        printf("second person singular");
        break;
    case SG_P3:
        printf("third person singular");
        break;
    case PL_P1:
        printf("first person plural");
        break;
    case PL_P2:
        printf("second person plural");
        break;
    case PL_P3:
        printf("third person plural");
        break;
    default:
        printf("i don't know which person sorry x'(");
        break;
    }
}

void printconjugaison(t_conjugaison conj)
{
    switch (conj.temps)
    {
    case Inf:
        printf("infinitive");
        break;
    case IImp:
        printf("indicative imperfect at the");
        printperson(conj.personne);
        break;
    case IPre:
        printf("indicative present at the");
        printperson(conj.personne);
        break;
    case IFut:
        printf("indicative future at the");
        printperson(conj.personne);
        break;
    case SPre:
        printf("subjonctive present at the");
        printperson(conj.personne);
        break;
    case IPsimp:
        printf("indicative simple past at the");
        printperson(conj.personne);
        break;
    case SImp:
        printf("subjonctive imperfect at the");
        printperson(conj.personne);
        break;
    case CPre:
        printf("condintional present at the");
        printperson(conj.personne);
        break;
    case PPre:
        printf("present participe");
        break;
    case PPas:
        printf("past participe");
        break;
    default:
        printf("verb ?");
        break;
    }
}
