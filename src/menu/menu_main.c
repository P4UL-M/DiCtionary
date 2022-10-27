/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main menu*/
#include "menu_main.h"
#include "menu_search.h"
#include "menu_generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../functions/search.h"
#include "../functions/dictionary.h"
#include "../types/struct.h"
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

void menu()
// Function that contains the main menu
{
    bool flag = true;
    while (flag)
    {
        title();
        int action;
        t_dictionary dico;
        do
        {
            printf("%sDo you want to:\n", ANSI_COLOR_GREEN);
            printf("%s1.%s Search for a word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s2.%s Generate a random sentence?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf("%s3.%s Exit?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
            printf(ANSI_COLOR_RESET);
            printf("\n>");
            scanf("%d", &action);
            fflush(stdin);
        } while (action < 1 || action > 3);
        switch (action)
        {
        case 1:
            search_menu(dico);
            break;
        case 2:
            generate_sentence(dico);
            break;
        default:
            flag = false;
            break;
        }
        waitKey();
    }
    return;
}

void search_menu(t_dictionary dico)
// Function to launch the search of a word
{
    title();
    printf("%sEnter the word you want to search:\n", ANSI_COLOR_GREEN);
    printf(ANSI_COLOR_RESET);
    printf("\n>");
    char searching[50];
    scanf("%50s", searching);
    p_node result = search(dico.nouns, searching);
    if (result != NULL)
    {
        p_form form = getForm(result, searching);
        printf("%s is a noun that is ", searching);
        displayResult(form);
        if (form->word != searching)
        {
            printf("It comes from %s, a noun that is ", result->forms->word);
            displayResult(result->forms);
        }
        return;
    }
    result = search(dico.adjectives, searching);
    if (result != NULL)
    {
        p_form form = getForm(result, searching);
        printf("%s is an adjective that is ", result->forms->word);
        displayResult(form);
        if (form->word != searching)
        {
            printf("It comes from %s, an adjective that is ", result->forms->word);
            displayResult(result->forms);
        }
        return;
    }
    p_node result = search(dico.adverbs, searching);
    if (result != NULL)
    {
        printf("%s is an adverb\n", result->forms->word);
        displayResult(result->forms);
        return;
    }
    p_node result = search(dico.verbs, searching);
    if (result != NULL)
    {
        p_form getForm(result, searching);
        printf("%s is a verb that is conjugated at the ", result->forms->word);
        displayResult(result->forms);
        if (form->word != searching)
        {
            printf("It comes from %s, a verb that is conjugated at the ", result->forms->word);
            displayResult(result->forms);
        }
        return;
    }
    printf("%s doesn't appear in the DiCtionary.\n", searching);
    return;
}

void generate_sentence_menu(t_dictionary dico)
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
    generate_sentence(generation_mode, dico);
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
