/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains functions to interact with the cache*/
#ifndef CACHE
#define CACHE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"
#include "../types/struct.h"

typedef struct
{
    p_node hash;
    UT_hash_handle hh;
} HashEntry;

void add_entry(p_node);  // add an entry to the cache
bool find_entry(p_node); // find an entry in the cache
void clear_cache();      // clear the cache

#endif