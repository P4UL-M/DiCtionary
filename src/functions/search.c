#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

p_node_noun searchNoun(p_tree_noun tree, char *noun)
{
    int foundletter;
    p_node_noun n=malloc(sizeof(p_node_noun));
    n=tree->children[noun[0]];
    for(int i=0;noun[i]!='\0';i++){
        foundletter=0;
        for(int j=97;j<MAX+97;j++){
            if(n->children[j]->value==noun[i]){
                foundletter=1;
                if(noun[i+1]=='\0'){
                    return n->children[j];
                }
                n=n->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
p_node_verb searchVerb(p_tree_verb tree, char *verb)
{
    int foundletter;
    p_node_verb n=malloc(sizeof(p_node_verb));
    n=tree->children[verb[0]];
    for(int i=0;verb[i]!='\0';i++){
        foundletter=0;
        for(int j=97;j<MAX+97;j++){
            if(n->children[j]->value==verb[i]){
                foundletter=1;
                if(verb[i+1]=='\0'){
                    return n->children[j];
                }
                n=n->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
p_node_adj searchAdj(p_tree_adj tree, char *adj)
{
    int foundletter;
    p_node_adj n=malloc(sizeof(p_node_adj));
    n=tree->children[adj[0]];
    for(int i=0;adj[i]!='\0';i++){
        foundletter=0;
        for(int j=97;j<MAX+97;j++){
            if(n->children[j]->value==adj[i]){
                foundletter=1;
                if(adj[i+1]=='\0'){
                    return n->children[j];
                }
                n=n->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
p_node_adv searchAdv(p_tree_adv tree, char *adv)
{
    int foundletter;
    p_node_adv n=malloc(sizeof(p_node_adv));
    n=tree->children[adv[0]];
    for(int i=0;adv[i]!='\0';i++){
        foundletter=0;
        for(int j=97;j<MAX+97;j++){
            if(n->children[j]->value==adv[i]){
                foundletter=1;
                if(adv[i+1]=='\0'){
                    return n->children[j];
                }
                n=n->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}

/*p_node_noun randomNoun(p_tree_noun tree){
    srand(time(0));
    p_node_noun n=malloc(sizeof(p_node_noun));
    n=tree->children[];
    char* word;
    for(int j=0;j<round(rand()*MAX);j++){
        int i=round(rand()*MAX); 
        word[j]=t->children[i];
    }
}

p_node_verb randomVerb(p_tree_verb tree);
p_node_adj randomAdj(p_tree_adj tree);
p_node_adv randomAdv(p_tree_adv tree); 
*/