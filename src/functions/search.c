#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

p_node_noun searchNoun(p_tree_noun tree, char *noun){
    p_node_noun n=malloc(sizeof(p_node_noun));
    n=tree->children[noun[0]];
    for(int i=1;noun[i]!='\0';i++){
        if(n->children[noun[i]]!=NULL){
            if(noun[i+1]=='\0'){
                return n->children[noun[i]];
            }
            n=n->children[noun[i]];
        }
        else{
            return NULL;
        }
    }
}

p_node_verb searchVerb(p_tree_verb tree, char *verb){
    p_node_verb n=malloc(sizeof(p_node_verb));
    n=tree->children[verb[0]];
    for(int i=1;verb[i]!='\0';i++){
        if(n->children[verb[i]]!=NULL){
            if(verb[i+1]=='\0'){
                return n->children[verb[i]];
            }
            n=n->children[verb[i]];
        }
        else{
            return NULL;
        }
    }
}

p_node_adj searchAdj(p_tree_adj tree, char *adj){
    p_node_adj n=malloc(sizeof(p_node_adj));
    n=tree->children[adj[0]];
    for(int i=1;adj[i]!='\0';i++){
        if(n->children[adj[i]]!=NULL){
            if(adj[i+1]=='\0'){
                return n->children[adj[i]];
            }
            n=n->children[adj[i]];
        }
        else{
            return NULL;
        }
    }
}

p_node_adv searchAdv(p_tree_adv tree, char *adv){
    p_node_adv n=malloc(sizeof(p_node_adv));
    n=tree->children[adv[0]];
    for(int i=1;adv[i]!='\0';i++){
        if(n->children[adv[i]]!=NULL){
            if(adv[i+1]=='\0'){
                return n->children[adv[i]];
            }
            n=n->children[adv[i]];
        }
        else{
            return NULL;
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