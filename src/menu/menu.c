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
            printf("%s1.%s Search for a word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s2.%s Generate a random sentence?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s3.%s Add a word in the dictionary?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s4.%s Exit?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf(ANSI_COLOR_RESET);
            printf("\n>");
            scanf("%d", &action);
            fflush(stdin);
        } while (action < 1 || action > 4);
        switch (action)
        {
        case 1:
            searchMenu(dico);
            waitKey();
            break;
        case 2:
            generateSentenceMenu(dico);
            waitKey();
            break;
        case 3:
            title();
            printf("%sEnter the word you want to add:\n", ANSI_COLOR_GREEN);
            printf(ANSI_COLOR_RESET);
            printf("\n>");
            char target[50];
            scanf("%50s", target);
            p_word word = getWord(dico.nouns, target, true);
            if (word == NULL)
            {
                word = getWord(dico.adjectives, target, true);
                if (word == NULL)
                {
                    word = getWord(dico.verbs, target, true);
                    if (word == NULL)
                    {
                        addToDico(dico, target);
                    }
                }
            }
            if (word != NULL)
            {
                printf("%sThe word already exists in the dictionary\n%s", ANSI_COLOR_RED, ANSI_COLOR_RESET);
                waitKey();
            }
            break;
        default:
            flag = false;
            break;
        }
    }
    return;
}

void searchMenu(t_dictionary dico)
// Function to launch the search of a word
{
    int trueSearch;
    printf("%sDo you want to search\n%s1.%s A simple word?\n%s2.%s A complex word?\n", ANSI_COLOR_GREEN, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        printf(ANSI_COLOR_RESET);
        printf("\n>");
        scanf("%d", &trueSearch);
        fflush(stdin);
    } while (trueSearch < 1 || trueSearch > 2);
    trueSearch--;
    int type;
    printf("%sWhat type of word do you want to search?\n%s1.%s Noun\n%s2.%s Adjective\n%s3.%s Adverb\n%s4.%s Verb\n%s5.%s Any", ANSI_COLOR_GREEN, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        printf(ANSI_COLOR_RESET);
        printf("\n>");
        scanf("%d", &type);
        fflush(stdin);
    } while (type < 1 || type > 5);
    title();
    printf("%sEnter the word you want to search:\n", ANSI_COLOR_GREEN);
    printf(ANSI_COLOR_RESET);
    printf("\n>");
    char target[50];
    scanf("%50s", target);
    fflush(stdin);
    searchword(dico, target, type, trueSearch);
}

void searchword(t_dictionary dico, char *target, int type, bool trueSearch)
{
    p_word result = NULL;
    p_form form = NULL;
    if (type == 1 || type == 5)
    {
        result = getWord(dico.nouns, target, trueSearch);
        form = getForm(result, target);
        if (result != NULL && form != NULL)
        {
            printf("%s is a noun that is ", target);
            displayForms(result, form);
            return;
        }
    }
    if (type == 2 || type == 5)
    {
        result = getWord(dico.adjectives, target, trueSearch);
        form = getForm(result, target);
        if (result != NULL && form != NULL)
        {
            printf("%s is an adjective that is ", target);
            displayForms(result, form);
            return;
        }
    }
    if (type == 3 || type == 5)
    {
        result = getWord(dico.adverbs, target, trueSearch);
        form = getForm(result, target);
        if (result != NULL && form != NULL)
        {
            printf("%s is an adverb that is ", target);
            displayForms(result, form);
            return;
        }
    }
    if (type == 4 || type == 5)
    {
        result = getWord(dico.verbs, target, trueSearch);
        form = getForm(result, target);
        if (result != NULL && form != NULL)
        {
            printf("%s is a verb that is ", target);
            displayForms(result, form);
            return;
        }
    }
    printf("%sThe word doesn't exist in the dictionary\n%s", ANSI_COLOR_CYAN, ANSI_COLOR_RESET);
    if (trueSearch)
    {
        int adding;
        do
        {
            printf("Do you want to add this word to the dictionnary?\n");
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
}

void generateSentenceMenu(t_dictionary dico)
// Function to generate a random sentence
{
    title();
    int generation_mode = 0, random_type = 0;
    printf("%sWhich type of random do you want ?\n%s1.%s Fastest one\n%s2.%s Most uniform one\n", ANSI_COLOR_GREEN, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        printf(ANSI_COLOR_RESET);
        printf("\n>");
        scanf("%d", &random_type);
        fflush(stdin);
    } while (random_type < 1 || random_type > 2);
    printf("%sWhich form of sentence do you want to generate?\n", ANSI_COLOR_GREEN);
    printf("%s1.%s Noun - Adjective - Verb - Noun\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    printf("%s2.%s Noun - \"qui\" - Verb - Verb - Noun - Adjective\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    printf("%s3.%s Case 3 not yet incorporated...\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        printf(ANSI_COLOR_RESET);
        printf(">");
        scanf("%d", &generation_mode);
        fflush(stdin);
    } while (generation_mode < 1 || generation_mode > 3); // Ne pas oublier l'easter egg
    p_word randomWord = getRandomWord(dico.verbs, 2);
    printf("%s", ANSI_COLOR_YELLOW);
    printf("the word is : %s", randomWord->base->word);
    // generate_sentence(generation_mode, random_type, dico);
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
    printf("IPre - IImp - SPre - SImp - IPSim - PPre - SImp - PPas - IFut - CPre - Inf\n");
    printf("Enter the tags of your word separated by a '+':\n>");
    char tags[50];
    scanf("%50s", tags);
    fflush(stdin);
    t_inputWord inputWord = {
        .word = word,
        .base = baseForm,
        .flags = tags};
    switch (type)
    {
    case 1:
        inputWord.type = NOUN_TYPE;
        addInTree(dico.nouns, word, baseForm, getFlags(tags));
        updateFile("data/dictionnaire.txt", inputWord);
        break;
    case 2:
        inputWord.type = ADJECTIVE_TYPE;
        addInTree(dico.adjectives, word, baseForm, getFlags(tags));
        updateFile("data/dictionnaire.txt", inputWord);
        break;
    case 3:
        inputWord.type = ADVERB_TYPE;
        addInTree(dico.adverbs, word, baseForm, getFlags(tags));
        updateFile("ata/dictionnaire.txt", inputWord);
        break;
    case 4:
        inputWord.type = VERB_TYPE;
        addInTree(dico.verbs, word, baseForm, getFlags(tags));
        updateFile("data/dictionnaire.txt", inputWord);
        break;
    }
}
