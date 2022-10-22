/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#include <stdio.h>
#include <stdlib.h>
#include "../types/adverbs.h"
#include "../types/nouns.h"
#include "../types/verbs.h"
#define ANSI_COLOR_RED "\x1b[0m\x1b[31;4m"
#define ANSI_COLOR_GREEN "\x1b[0m\x1b[32;1;3m"
#define ANSI_COLOR_YELLOW "\x1b[0m\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[0m\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[0m\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[0m\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_BACKGROUND_WHITE "\x1b[0m\x1b[39;1m\e[47m\e[K"

void displayDeclinaison(t_declinaison_noun decli)
// To print the form of the noun
{
    printf("%s that is ", decli.word);
    switch (decli.forme)
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

void displayNoun(t_noun noun)
// To print all declinaisons for the noun
{
    displayDeclinaison(noun.declinaisons[noun.studyIndex]);
    printf("\n");
    if (noun.declinaisons == NULL)
    {
        printf("It has no other form\n");
        return;
    }
    printf("Its derivatives are :\n");
    for (int i = 0; i < noun.nb_declinaisons; i++)
    {
        if (i != noun.studyIndex)
        {
            printf("-> ");
            displayDeclinaison(noun.declinaisons[i]);
            printf("\n");
        }
    }
}

void dysplayPerson(t_personne pers)
// To print the details for the person of the verb
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

void displayConjugaison(t_conjugaison conj)
// To print the details of the conjugaison of the verb
{
    printf("%s that is ", conj.word);
    switch (conj.temps)
    {
    case Inf:
        printf("infinitive");
        break;
    case IImp:
        printf("indicative imperfect at the");
        dysplayPerson(conj.personne);
        break;
    case IPre:
        printf("indicative present at the");
        dysplayPerson(conj.personne);
        break;
    case IFut:
        printf("indicative future at the");
        dysplayPerson(conj.personne);
        break;
    case SPre:
        printf("subjonctive present at the");
        dysplayPerson(conj.personne);
        break;
    case IPsimp:
        printf("indicative simple past at the");
        dysplayPerson(conj.personne);
        break;
    case SImp:
        printf("subjonctive imperfect at the");
        dysplayPerson(conj.personne);
        break;
    case CPre:
        printf("condintional present at the");
        dysplayPerson(conj.personne);
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

void displayVerb(t_verb verb)
// To print all conjugaisons of the verb
{
    displayConjugaison(verb.conjugaisons[verb.studyIndex]);
    printf("\n");
    if (verb.conjugaisons == NULL)
    {
        printf("It has no other form\n");
        return;
    }
    printf("Its derivatives are :\n");
    for (int i = 0; i < verb.nb_conjugaisons; i++)
    {
        if (i != verb.studyIndex)
        {
            displayConjugaison(verb.conjugaisons[i]);
            printf("\n");
        }
    }
}
