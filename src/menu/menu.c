/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main menu*/
#include "menu.h"
#include "display.h"
#include "input.h"
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
    wprintf(L"%ls\tWelcome in the DiCtionary%ls\t\n\n", ANSI_BACKGROUND_WHITE, ANSI_COLOR_RESET);
}

void menu(t_dictionary dico)
// Function that contains the main menu
{
    srand(time(NULL));
    bool flag = true;
    while (flag)
    {
        int action;
        do
        {
            title();
            wprintf(L"%lsDo you want to:\n", ANSI_COLOR_GREEN);
            wprintf(L"%ls1.%ls Search for a word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            wprintf(L"%ls2.%ls Generate a random sentence?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            wprintf(L"%ls3.%ls Add a word in the dictionary?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            wprintf(L"%ls4.%ls Exit?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            wprintf(ANSI_COLOR_RESET);
            wprintf(L"\n>");
            scanf("%d", &action);
            fflush(stdin);
        } while (action < 1 || action > 4);
        switch (action)
        {
        case 1:
            title();
            searchMenu(dico);
            waitKey();
            break;
        case 2:
            title();
            generateSentenceMenu(dico);
            waitKey();
            break;
        case 3:
            title();
            wprintf(L"%lsEnter the word you want to add:\n", ANSI_COLOR_GREEN);
            wprintf(ANSI_COLOR_RESET);
            wprintf(L"\n>");
            wchar_t target[50];
            scanf("%50ls", target);
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
                wprintf(L"%lsThe word already exists in the dictionary\n%ls", ANSI_COLOR_RED, ANSI_COLOR_RESET);
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
    wprintf(L"%lsDo you want to search\n%ls1.%ls A simple word?\n%ls2.%ls A complex word?\n", ANSI_COLOR_GREEN, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        wprintf(ANSI_COLOR_RESET);
        wprintf(L"\n>");
        scanf("%d", &trueSearch);
        fflush(stdin);
    } while (trueSearch < 1 || trueSearch > 2);
    trueSearch--;
    int type;
    title();
    wprintf(L"%lsWhat type of word do you want to search?\n%ls1.%ls Noun\n%ls2.%ls Adjective\n%ls3.%ls Adverb\n%ls4.%ls Verb\n%ls5.%ls Any", ANSI_COLOR_GREEN, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        wprintf(ANSI_COLOR_RESET);
        wprintf(L"\n>");
        scanf("%d", &type);
        fflush(stdin);
    } while (type < 1 || type > 5);
    title();
    wprintf(L"%lsEnter the word you want to search:\n", ANSI_COLOR_GREEN);
    wprintf(ANSI_COLOR_RESET);
    wprintf(L"\n>");
    wchar_t target[50];
    scanAutoCompletion(dico, target, type);
    fflush(stdin);
    title();
    searchword(dico, target, type, trueSearch);
}

void searchword(t_dictionary dico, wchar_t *target, int type, bool trueSearch)
{
    p_word result = NULL;
    p_form form = NULL;
    if (type == 1 || type == 5)
    {
        result = getWord(dico.nouns, target, trueSearch);
        if (result != NULL)
            form = getForm(*result, target);
        if (result != NULL && form != NULL)
        {
            wprintf(L"%ls is a noun that is ", target);
            displayForms(*result, *form);
            return;
        }
    }
    if (type == 2 || type == 5)
    {
        result = getWord(dico.adjectives, target, trueSearch);
        if (result != NULL)
            form = getForm(*result, target);
        if (result != NULL && form != NULL)
        {
            wprintf(L"%ls is an adjective that is ", target);
            displayForms(*result, *form);
            return;
        }
    }
    if (type == 3 || type == 5)
    {
        result = getWord(dico.adverbs, target, trueSearch);
        if (result != NULL)
            form = getForm(*result, target);
        if (result != NULL && form != NULL)
        {
            wprintf(L"%ls is an adverb that is ", target);
            displayForms(*result, *form);
            return;
        }
    }
    if (type == 4 || type == 5)
    {
        result = getWord(dico.verbs, target, trueSearch);
        if (result != NULL)
            form = getForm(*result, target);
        if (result != NULL && form != NULL)
        {
            wprintf(L"%ls is a verb that is ", target);
            displayForms(*result, *form);
            return;
        }
    }
    wprintf(L"%lsThe word doesn't exist in the dictionary\n%ls", ANSI_COLOR_CYAN, ANSI_COLOR_RESET);
    if (trueSearch)
    {
        int adding;
        do
        {
            wprintf(L"Do you want to add this word to the dictionnary?\n");
            wprintf(L"%ls1.%ls Yes\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            wprintf(L"%ls2.%ls No", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            wprintf(ANSI_COLOR_RESET);
            wprintf(L"\n>");
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
    wprintf(L"%lsWhich type of random do you want ?\n%ls1.%ls Fastest one\n%ls2.%ls Most uniform one\n", ANSI_COLOR_GREEN, ANSI_COLOR_RED, ANSI_COLOR_BLUE, ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        wprintf(ANSI_COLOR_RESET);
        wprintf(L"\n>");
        scanf("%d", &random_type);
        fflush(stdin);
    } while (random_type < 1 || random_type > 2);
    title();
    wprintf(L"%lsWhich form of sentence do you want to generate?\n", ANSI_COLOR_GREEN);
    wprintf(L"%ls1.%ls Noun - Adjective - Verb - Noun\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    wprintf(L"%ls2.%ls Noun - \"qui\" - Verb - Verb - Noun - Adjective\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    wprintf(L"%ls3.%ls Verb - Noun - Past Participe - \"que\" - Subjonctif - Noun\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
    do
    {
        wprintf(ANSI_COLOR_RESET);
        wprintf(L"\n>");
        scanf("%d", &generation_mode);
        fflush(stdin);
    } while (generation_mode < 1 || generation_mode > 3); // Ne pas oublier l'easter egg
    title();
    wprintf(L"%lsSentence :%ls\n\n> ", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    generateSentence(dico, generation_mode, random_type);
}

void waitKey()
// Function to wait for the users in resolution
{
    fflush(stdin);
    wprintf(L"\nPress a key to continue...\n");
    sleep(1);
    while (1)
    {
        if (getKeyFunc())
        {
            fflush(stdin);
            break;
        }
    }
}

void addToDico(t_dictionary dico, wchar_t *word)
{
    int type;
    title();
    do
    {
        wprintf(L"%lsWhat is the type of the word?\n", ANSI_COLOR_GREEN);
        wprintf(L"%ls1.%ls Noun\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        wprintf(L"%ls2.%ls Adjective\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        wprintf(L"%ls3.%ls Adverb\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        wprintf(L"%ls4.%ls Verb\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        wprintf(ANSI_COLOR_RESET);
        wprintf(L"\n>");
        scanf("%d", &type);
        fflush(stdin);
    } while (type < 1 || type > 4);
    title();
    wprintf(L"%lsIs your word the base form of the word? (1 for yes, 2 for no)%ls\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
    int base;
    do
    {
        wprintf(L"\n>");
        scanf("%d", &base);
        fflush(stdin);
    } while (base < 1 || base > 2);
    wchar_t baseForm[50];
    if (base - 1)
    {
        title();
        wprintf(L"%lsWhat is the base form of the word?%ls\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
        do
        {
            wprintf(L"\n>");
            scanf("%50ls", baseForm);
            fflush(stdin);
        } while (wcslen(baseForm) < 1);
    }
    else
        wcscpy(baseForm, word);
    title();
    wprintf(L"%lsEnter the tags of your word separated by a '+' :\n\n", ANSI_COLOR_GREEN);
    wprintf(L"%lsAll the possible tags are :\n", ANSI_COLOR_RED);
    wprintf(L"%ls> SG - PL\n> Mas - Fem\n> P1 - P2 - P3\n", ANSI_COLOR_CYAN);
    wprintf(L"> IPre - IImp - SPre - SImp - IPSim - PPre - SImp - PPas - IFut - CPre - Inf\n\n%ls>", ANSI_COLOR_RESET);
    wchar_t tags[50];
    scanf("%50ls", tags);
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
