#include "dictionary.h"
#include "adverbs.h"
#include "nouns.h"
#include "verbs.h"

char* searchnoun(t_tree_noun t,char* word);
char* searchadjective(t_tree_adj t,char* word);
char* searchadverb(t_tree_adv t,char* word);
char* searchverb(t_tree_verb t,char* word);