/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the menu*/
#include "menu.h"
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#define CLEAR "cls"
#define sleep Sleep
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

void menu()
{
    int action;
    do
    {
        system(CLEAR);
        printf("Welcome in the DiCtionary\nDo you want to :\n1.Search for a word?\n2.Generate a random sentence?\n(Type 1 or 2)\n>");
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