/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/struct.h"

void displayVerb();
void displayConjugaison();
void displayPerson();
void displayForm(p_form, int);
void displayDeclinaison();

#endif