/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types/struct.h"
#include "functions/dictionary.h"
//#include "menu/menu_main.h"
#include "functions/search.h"
#include "menu/menu_main.h"

int main()
{
    clock_t t;
    t = clock();
    printf("Hello world\n");
    t_dictionary dictionary = extractFile("data/dictionnaire.txt");
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    menu();
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}