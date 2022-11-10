/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main algorithm*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "types/struct.h"
#include "functions/dictionary.h"
#include "functions/search.h"
#include "functions/random.h"
#include "menu/menu.h"

int main()
{
    clock_t t;
    t = clock();
    printf("Hello world\n");
    t_dictionary dictionary = extractFile("data/dictionnaire.txt");
    printf("time of execution: %f seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    buildPonderation(dictionary.nouns);
    buildPonderation(dictionary.adjectives);
    buildPonderation(dictionary.verbs);
    buildPonderation(dictionary.adverbs);
    buildPonderation(dictionary.pronouns);
    buildPonderation(dictionary.determinants);
    menu(dictionary);
    printf("time of execution: %f seconds", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}