#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/nouns.h"
#include "../types/verbs.h"
#include "../types/adverbs.h"

p_noun searchNoun(p_tree_noun tree, char *noun)
{
    int foundletter;
    p_tree_noun t=malloc(sizeof(t_tree_noun));
    t=tree;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t->children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return t->children[j];
                }
                t=t->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
p_verb searchVerb(p_tree_verb tree, char *verb)
{
    int foundletter;
    p_tree_verb t=malloc(sizeof(t_tree_verb));
    t=tree;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t->children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return t->children[j];
                }
                t=t->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
p_adj searchAdj(p_tree_adj tree, char *adj)
{
    int foundletter;
    p_tree_adj t=malloc(sizeof(t_tree_adj));
    t=tree;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t->children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return t->children[j];
                }
                t=t->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
p_adv searchAdv(p_tree_adv tree, char *adv)
{
    int foundletter;
    p_tree_adv t=malloc(sizeof(t_tree_adv));
    t=tree;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t->children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return t->children[j];
                }
                t=t->children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}

p_noun randomNoun(p_tree_noun tree){

}

p_verb randomVerb(p_tree_verb tree);
p_adj randomAdj(p_tree_adj tree);
p_adv randomAdv(p_tree_adv tree);