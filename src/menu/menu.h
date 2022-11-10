/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the main menu*/
#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "../functions/dictionary.h"

void menu(t_dictionary);
void searchMenu(t_dictionary);
void searchword(t_dictionary dico, char *target, int type, bool trueSearch);
void generateSentenceMenu(t_dictionary);
void waitKey();
void addToDico(t_dictionary, char *);

#endif