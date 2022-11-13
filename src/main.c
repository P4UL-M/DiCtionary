/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <wchar.h>

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
    wchar_t test[5];
    scanf("%5ls", test);
    wchar_t test2[5];
    scanf("%5ls", test2);
    wchar_t *test3;
    test3 = wcscat(test, test2);
    printf("%ls\n", test3);
    t_dictionary dictionary = extractFile("data/sorted_dictionnaire.txt");
    printf("time of execution: %f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    buildPonderations(dictionary);
    menu(dictionary);
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}