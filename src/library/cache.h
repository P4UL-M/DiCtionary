/*TaCuzu
Paul Mairesse and Axel Loones
This file contains function to interact with the cache*/
#ifndef CACHE
#define CACHE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"
#include "../types/struct.h"

typedef struct
{
    long long int hash;
    p_node *node;
    UT_hash_handle hh;
} HashEntry;

void add_entry(long long int, p_node); // add an entry to the cache
p_node find_entry(int);                // find an entry in the cache

#endif