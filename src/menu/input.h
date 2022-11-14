/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the functions to adapt the search in the menu*/
#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../functions/dictionary.h"

wchar_t *getKeyFunc();
wchar_t *scanAutoCompletion(t_dictionary, wchar_t *, int);

#endif