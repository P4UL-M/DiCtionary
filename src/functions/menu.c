/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the menu*/
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
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
{
    int action;
    system(CLEAR);
    printf("%s\tWelcome in the DiCtionary\t\n\n", ANSI_BACKGROUND_WHITE);
    do
    {
        printf("%sDo you want to :\n", ANSI_COLOR_GREEN);
        printf("%s1.%s Search for a word?\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
        printf("%s2.%s Generate a random sentence? (Type 1 or 2)\n", ANSI_COLOR_RED, ANSI_COLOR_BLUE);
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
{
    printf("Hello\n");
}

void generate_sentence()
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