/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#ifndef MENU_SEARCH_H
#define MENU_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

void displayVerb(p_verb vers);
void displayConjugaison(t_conjugaison conj);
void dysplayPerson(t_personne pers);
void displayNoun(p_noun vers);
void displayDeclinaison(t_forme_noun forme);

#endif