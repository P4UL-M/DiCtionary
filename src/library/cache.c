/*TaCuzu
Paul Mairesse and Axel Loones
This file contains function to interact with the cache*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "uthash.h" // librairy for hash table
#include "../types/struct.h"
#include "cache.h"

HashEntry *mycache = NULL;

void add_entry(long long int hash, p_node node)
{
    // add an entry to the cache
    HashEntry *s = (HashEntry *)malloc(sizeof(HashEntry));
    s->node = node;
    s->hash = hash;
    HASH_ADD_INT(mycache, hash, s); // add the entry to the cache with uthash
}

p_node find_entry(int hashCode)
{
    // find an entry in the cache
    HashEntry *s;
    HASH_FIND_INT(mycache, &hashCode, s); // find the entry in the cache with uthash
    if (s != NULL)
    {
        return s->node;
    }
    return NULL;
}
