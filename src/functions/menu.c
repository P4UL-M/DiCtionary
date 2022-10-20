/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the menu*/
#include "menu.h"
#include <stdio.h>
#include "search.h"
#ifdef _WIN32
#include <Windows.h>
#define CLEAR "cls"
#define sleep Sleep
#else
#include <unistd.h>
#define CLEAR "clear"
#endif
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void menu()
{
    int action;
    system(CLEAR);
    printf(ANSI_COLOR_GREEN);
    printf("Welcome in the DiCtionary\n");
    printf(ANSI_COLOR_BLUE);
    do
    {
        printf("Do you want to :\n1.Search for a word?\n2.Generate a random sentence?\n(Type 1 or 2)\n");
        printf(ANSI_COLOR_RESET);
        printf(">");
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
    sleep(0.5f);
    while (1)
    {
        if (getchar())
        {
            fflush(stdin);
            break;
        }
    }
}