/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains functions to interact with the cache*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "uthash.h" // librairy for hash table
#include "../types/struct.h"
#include "cache.h"

HashEntry *mycache = NULL;

void add_entry(p_node hash)
{
    // add an entry to the cache
    HashEntry *s = (HashEntry *)malloc(sizeof(HashEntry));
    s->hash = hash;
    HASH_ADD_PTR(mycache, hash, s); // add the entry to the cache with uthash
}

bool find_entry(p_node hashCode)
{
    // find an entry in the cache
    HashEntry *s;
    HASH_FIND_PTR(mycache, &hashCode, s); // find the entry in the cache with uthash
    return (s != NULL);
}

void clear_cache()
{
    // clear the cache
    HashEntry *current_entry, *tmp;
    HASH_ITER(hh, mycache, current_entry, tmp)
    {
        HASH_DEL(mycache, current_entry); // delete the entry from the cache with uthash
        free(current_entry);              // free the memory
    }
}
