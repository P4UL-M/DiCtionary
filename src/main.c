/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

#include "types/struct.h"
#include "functions/dictionary.h"
#include "functions/search.h"
#include "functions/random.h"
#include "menu/menu.h"

int main()
{
    clock_t t;
    t = clock();
    setlocale(LC_ALL, "");
    t_dictionary dictionary = extractFile("data/sorted_dictionnaire.txt");
    printf("time of execution: %f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    buildPonderations(dictionary);
    menu(dictionary);
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}