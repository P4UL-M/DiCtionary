/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main menu*/
#include "menu.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../functions/search.h"
#include "../functions/dictionary.h"
#include "../functions/sentence.h"
#include "../functions/random.h"
#include "../types/struct.h"
#include "../library/cache.h"
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

void title()
{
    system(CLEAR);
    printf("%s\tWelcome in the DiCtionary\t\n\n", ANSI_BACKGROUND_WHITE);
}

void menu(t_dictionary dico)
// Function that contains the main menu
{
    srand(time(NULL));
    bool flag = true;
    printf("NUMBERS OF NOUNS: %d\n", dico.verbs->ponderation);
    buildPonderation(dico.verbs);
    printf("NUMBERS OF NOUNS: %d\n", dico.verbs->ponderation);
    p_word randomWord;
    while (flag)
    {
        int action;
        do
        {
            title();
            printf("%sDo you want to:\n", ANSI_COLOR_GREEN);
            printf("%s1.%s Search for a basic word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s2.%s Search for a word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s3.%s Generate a random sentence?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s4.%s Exit?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf(ANSI_COLOR_RESET);
            printf("\n>");
            scanf("%d", &action);
            fflush(stdin);
        } while (action < 1 || action > 4);
        switch (action)
        {
        case 1:
            searchMenu(dico, false);
            waitKey();
            break;
        case 2:
            searchMenu(dico, true);
            waitKey();
            break;
        case 3:
            randomWord = getRandomWord(dico.verbs, 2);
            printf("%s", ANSI_COLOR_YELLOW);
            printf("the word is : %s", randomWord->base->word);
            // generateSentence(1,dico);
            waitKey();
            break;
        default:
            flag = false;
            break;
        }
    }
    return;
}

void searchMenu(t_dictionary dico, bool trueSearch)
// Function to launch the search of a word
{
    title();
    printf("%sEnter the word you want to search:\n", ANSI_COLOR_GREEN);
    printf(ANSI_COLOR_RESET);
    printf("\n>");
    char target[50];
    scanf("%50s", target);
    printf("%s\nSearching in Nouns...%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    p_word result = getWord(dico.nouns, target, trueSearch);
    p_form form = getForm(result, target);
    if (result != NULL && form != NULL)
    {
        printf("%s is a noun that is ", target);
        displayForms(result, form);
        return;
    }
    printf("%s\nSearching in Adjectives...%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    result = getWord(dico.adjectives, target, trueSearch);
    form = getForm(result, target);
    if (result != NULL && form != NULL)
    {
        printf("%s is an adjective that is ", target);
        displayForms(result, form);
        return;
    }
    printf("%s\nSearching in Adverbs...%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    result = getWord(dico.adverbs, target, trueSearch);
    if (result != NULL)
    {
        printf("%s is an adverb\n", target);
        return;
    }
    printf("%s\nSearching in Verbs...%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    result = getWord(dico.verbs, target, trueSearch);
    form = getForm(result, target);
    if (result != NULL && form != NULL)
    {
        printf("%s is a verb that is ", target);
        displayForms(result, form);
        return;
    }
    int adding;
    do
    {
        printf("%sDo you want to add this word to the dictionnary?\n", ANSI_COLOR_GREEN);
        printf("%s1.%s Yes\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf("%s2.%s No", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf(ANSI_COLOR_RESET);
        printf("\n>");
        scanf("%d", &adding);
        fflush(stdin);
    } while (adding < 1 || adding > 2);
    if (adding - 1)
        return;
    addToDico(dico, target);
}

void generateSentenceMenu(t_dictionary dico)
// Function to generate a random sentence
{
    title();
    int generation_mode = 0;
    printf(ANSI_COLOR_RESET);
    printf("Which form of sentence do you want to generate?\n");
    printf("1. Noun - Adjective - Verb - Noun\n");
    printf("2. Noun - \"qui\" - Verb - Verb - Noun - Adjective\n");
    printf("3. Case 3 not yet incorporated...\n");
    do
    {
        printf(">");
        scanf("%d", &generation_mode);
        fflush(stdin);
    } while (generation_mode < 1 || generation_mode > 3); // Ne pas oublier l'easter egg
    // generate_sentence(generation_mode, dico);
}

void waitKey()
// Function to wait for the users in resolution
{
    fflush(stdin);
    printf("\nPress a key to continue...\n");
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

void addToDico(t_dictionary dico, char *word)
{
    int type;
    do
    {
        printf("%sWhat is the type of the word?\n", ANSI_COLOR_GREEN);
        printf("%s1.%s Noun\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf("%s2.%s Adjective\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf("%s3.%s Adverb\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf("%s4.%s Verb\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf(ANSI_COLOR_RESET);
        printf("\n>");
        scanf("%d", &type);
        fflush(stdin);
    } while (type < 1 || type > 4);
    printf("Is your word the base form of the word? (1 for yes, 2 for no)\n");
    int base;
    do
    {
        printf(">");
        scanf("%d", &base);
        fflush(stdin);
    } while (base < 1 || base > 2);
    char baseForm[50];
    if (base - 1)
    {
        printf("What is the base form of the word?\n");
        do
        {
            printf(">");
            scanf("%50s", baseForm);
            fflush(stdin);
        } while (strlen(baseForm) < 1);
    }
    else
        strcpy(baseForm, word);
    printf("All the possible tags are:\n");
    printf("SG - PL\nMas - Fem\nP1 - P2 - P3\n");
    printf("IPre - IImp - SPre - SImp - IPsimp - PPre - SImp - PPas - IFut - CPre - Inf\n");
    printf("Enter the tags of your word separated by a '+':\n>");
    char tags[50];
    scanf("%50s", tags);
    fflush(stdin);
    switch (type)
    {
    case 1:
        addInTree(dico.nouns, word, baseForm, getFlags(tags));
        break;
    case 2:
        addInTree(dico.adjectives, word, baseForm, getFlags(tags));
        break;
    case 3:
        addInTree(dico.adverbs, word, baseForm, getFlags(tags));
        break;
    case 4:
        addInTree(dico.verbs, word, baseForm, getFlags(tags));
        break;
    }
}
