#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "adverbs.h"
#include "nouns.h"
#include "verbs.h"

char* searchnoun(t_tree_noun t,char* word){
    int foundletter;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t.children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return 1;
                }
                t=t.children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}

char* searchadjective(t_tree_adj t,char* word){
    int foundletter;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t.children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return 1;
                }
                t=t.children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}

char* searchadverb(t_tree_adv t,char* word){
    int foundletter;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t.children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return 1;
                }
                t=t.children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}

char* searchverb(t_tree_verb t,char* word){
    int foundletter;
    for(int i=0;word[i]!='0';i++){
        foundletter=0;
        for(int j=0;j<MAX;j++){
            if(t.children[j]==word[i]){
                foundletter=1;
                if(word[i+1]=='0'){
                    return 1;
                }
                t=t.children[j];
            }
        }
        if(foundletter==0){
            return 0;
        }
    }
}
