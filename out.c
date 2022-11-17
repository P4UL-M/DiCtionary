/*
This file is the easter egg of the project.
It contains hidden functions that generate another type of sentence.
Those functions are totally useless to the project but are here for fun.
*/
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "menu.h"
#include "easteregg.h"
#include "../types/constants.h"
#include "../types/struct.h"
#include "../functions/random.h"
#include <stdbool.h>
#include <wchar.h>
#include "../functions/dictionary.h"
#include "../functions/search.h"
#include "../menu/display.h"
#define o_127a457484362975775020898a7e8038 malloc
#define o_2f5b67a3f90cc3b7bab04c6d937b75a8 calloc
#define o_22f963af3a82075f9fe12614af395e64 free
#define o_86625afd559ad8fb8d6241793615b5fd waitKey
#define o_63e049e1f9acd3e1be1f727f8316ed7d printf
#define o_2dd6d89172322d540480683668139154 rand
#define o_70f3b0f3f9b0f3f9b0f3f9b0f3f9b0f3 srand
#define o_32f5b47a3f90cc3b7bab04c6d937b75a8 scanf
#define o_62f5b47a3f90cc3b7bab04c6d937b75a8 int
#define o_72f5b47a3f90cc3b7bab04c6d937b75a8 char
#define o_82f5b47a3f90cc3b7bab04c6d937b75a8 float
#define o_92f5b47a3f90cc3b7bab04c6d937b75a8 double
#define o_ae12c59305e73eb77e32401e6aec482ef void
#define o_99f5b47a3f90cc3b7bab04c6d937b75a8 return
#define o_89f5b47a3f90cc3b7bab04c6d937b75a8 else
#define o_79f5b47a3f90cc3b7bab04c6d937b75a8 if
#define o_69f5b47a3f90cc3b7bab04c6d937b75a8 for
#define o_59f5b47a3f90cc3b7bab04c6d937b75a8 while
#define o_49f5b47a3f90cc3b7bab04c6d937b75a8 do
#define o_39f5b47a3f90cc3b7bab04c6d937b75a8 switch
#define o_29f5b47a3f90cc3b7bab04c6d937b75a8 case
#define o_19f5b47a3f90cc3b7bab04c6d937b75a8 default
#define o_09f5b47a3f90cc3b7bab04c6d937b75a8 break
#define o_0af5b47a3f90cc3b7bab04c6d937b75a8 continue
#define o_0bf5b47a3f90cc3b7bab04c6d937b75a8 typedef
#define o_0cf5b47a3f90cc3b7bab04c6d937b75a8 struct
#define o_0df5b47a3f90cc3b7bab04c6d937b75a8 union
#define o_0ef5b47a3f90cc3b7bab04c6d937b75a8 enum
#define o_0ff5b47a3f90cc3b7bab04c6d937b75a8 goto
#define o_0gf5b47a3f90cc3b7bab04c6d937b75a8 sizeof
#define o_0hf5b47a3f90cc3b7bab04c6d937b75a8 static
#define o_8f5b47a3f90cc3b7bab04c6d937b75a8 o_62f5b47a3f90cc3b7bab04c6d937b75a8
#define o_9f5b47a3f90cc3b7bab04c6d937b75a8 o_ae12c59305e73eb77e32401e6aec482ef
#define o_af5b47a3f90dc3b7bab04c6d937b75a8 NULL

p_form o_af5b47a3f90cc3b7bab04c6d937b75a8(p_word word, unsigned int tag)
// Find the form we want in the word
{
    t_node temp = {
        .forms = word->forms,
    };
    return getFormByTag(temp, tag);
}

wchar_t *o_azf5b47a3f90cc3b7bab04c6d937b75a8(wchar_t *sentence)
// Make the sentence more beautiful
{
    wchar_t *output = sentence;
    // detect le, la, les, l' and l
    wchar_t *index = output;
    while ((index = wcschr(index, L'l')) != NULL)
    {
        if (wcspbrk(index, L"ae") == index + 1 && wcschr(index, L' ') == index + 2 && (index == output || *(index - 1) == L' '))
        {
            wchar_t *next = index + 3;
            if (wcspbrk(next, L"aeiouyéèê") == next)
            {
                *(index + 1) = '\'';
                wmemmove(index + 2, index + 3, wcslen(index + 3) + 1);
            }
        }
        index += 3;
    }
    // detect je to j'
    index = output;
    while ((index = wcschr(index, L'j')) != NULL)
    {
        if (wcspbrk(index, L"e") == index + 1 && wcschr(index, L' ') == index + 2 && (index == output || *(index - 1) == L' '))
        {
            wchar_t *next = index + 3;
            if (wcspbrk(next, L"aeiouyéèê") == next)
            {
                *(index + 1) = '\'';
                wmemmove(index + 2, index + 3, wcslen(index + 3) + 1);
            }
        }
        index += 3;
    }
    // detect que to qu'
    index = output;
    while ((index = wcschr(index, L'q')) != NULL)
    {
        if (wcspbrk(index, L"u") == index + 1 && wcschr(index, L'e') == index + 2 && wcschr(index, L' ') == index + 3 && (index == output || *(index - 1) == L' '))
        {
            wchar_t *next = index + 4;
            if (wcspbrk(next, L"aeiouyéèê") == next)
            {
                *(index + 2) = '\'';
                wmemmove(index + 3, index + 4, wcslen(index + 4) + 1);
            }
        }
        index += 4;
    }
    // remove space before ponctuation
    index = output;
    while ((index = wcschr(index, L' ')))
    {
        if (wcschr(index, L'.') == index + 1)
        {
            wmemmove(index, index + 1, wcslen(index));
        }
        index++;
    }
    // make first letter uppercase
    *output = towupper(*output);
    // make sure last character is \0
    output[wcslen(output)] = L'\0';
    return output;
}

p_form o_bz5b47a3f90cc3b7bab04c6d937b75a8(p_word word, unsigned int mask, unsigned int antimask)
// Find a random word with specifications : mask is what we want as tag, antimask what we don't want
{
    p_form form = word->forms;
    int count = 0;
    p_form *forms = malloc(sizeof(p_form));
    while (form != NULL)
    {
        if ((form->tag & mask) == mask && (antimask == 0 || (form->tag & antimask) == 0))
        {

            count++;
            forms = realloc(forms, count * sizeof(p_form));
            forms[count - 1] = form;
        }
        form = form->next;
    }
    if (count == 0)
    {
        free(forms);
        return NULL;
    }
    unsigned int index = rand() % count;
    p_form result = forms[index];
    free(forms);
    return result;
}

t_word o_cz5b47a3f90cc3b7bab04c6d937b75a8(t_dictionary dico)
// Get a personal pronoun
{
    wchar_t *pronouns[9] = {L"je", L"tu", L"il", L"elle", L"on", L"nous", L"vous", L"ils", L"elles"};
    int tags[9] = {};
    for (int i = 0; i < 9; i++)
    {
        p_word word = getWord(dico.pronouns, pronouns[i], false);
        if (word != NULL)
        {
            tags[i] = word->forms->tag;
        }
    }
    t_node node = {};
    for (int i = 0; i < 9; i++)
    {
        addForm(&node, pronouns[i], tags[i]);
    }
    t_word result = {
        .forms = node.forms,
    };
    return result;
}

o_8f5b47a3f90cc3b7bab04c6d937b75a8 o_2f5b47a3f90cc3b7bab04c6d937b75a8() { o_99f5b47a3f90cc3b7bab04c6d937b75a8((0x00000000000004CC + 0x0000000000000466 + 0x0000000000000A66 - 0x0000000000001132) + (0x0000000000000666 + 0x0000000000000533 + 0x0000000000000B33 - 0x0000000000001399) + (0x0000000000001266 + 0x0000000000000B33 + 0x0000000000001133 - 0x0000000000002599) - (0x0000000000001B32 + 0x0000000000000F99 + 0x0000000000001599 - 0x00000000000032CB)); };

o_9f5b47a3f90cc3b7bab04c6d937b75a8 o_ae12c59305e73eb77e32401e6aec482e(o_8f5b47a3f90cc3b7bab04c6d937b75a8 o_75c60826c17602610e9094188f27c3bf, t_dictionary o_5357eac91da00909c7d7c18d3287347c)
{
    o_62f5b47a3f90cc3b7bab04c6d937b75a8 *o_7bd94c6dc607b573e0cac21b6b9c0fd0 = o_127a457484362975775020898a7e8038(o_0gf5b47a3f90cc3b7bab04c6d937b75a8(o_62f5b47a3f90cc3b7bab04c6d937b75a8));
    *o_7bd94c6dc607b573e0cac21b6b9c0fd0 = o_2dd6d89172322d540480683668139154() % ((0x000000000000005C + 0x000000000000022E + 0x000000000000082E - 0x0000000000000A8A) + (0x000000000000042E + 0x0000000000000417 + 0x0000000000000A17 - 0x0000000000001045) + (0x000000000000102E + 0x0000000000000A17 + 0x0000000000001017 - 0x0000000000002245) - (0x000000000000148A + 0x0000000000000C45 + 0x0000000000001245 - 0x00000000000028CF));
    ;
    o_79f5b47a3f90cc3b7bab04c6d937b75a8(!(o_75c60826c17602610e9094188f27c3bf ^ o_2f5b47a3f90cc3b7bab04c6d937b75a8()))
    {
        o_63e049e1f9acd3e1be1f727f8316ed7d("\x1B"
                                           "[\060m\x1B"
                                           "[\0631\x3B"
                                           "4\155Y\x6F"
                                           "u\040f\x6F"
                                           "u\156d\x20"
                                           "t\150e\x20"
                                           "e\141s\x74"
                                           "e\162 \x65"
                                           "g\147!\x0A"
                                           "\x1B\1330\x6D"
                                           "");
    };
    ;
    o_22f963af3a82075f9fe12614af395e64(o_7bd94c6dc607b573e0cac21b6b9c0fd0);
    ;
    p_form o_f9c4fad3b5e738b92096dd165dad3b5b[(0x0000000000000008 + 0x0000000000000204 + 0x0000000000000804 - 0x0000000000000A0C)];
    o_49f5b47a3f90cc3b7bab04c6d937b75a8
    {
        *(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00)) = o_bz5b47a3f90cc3b7bab04c6d937b75a8(getRandomWord(o_5357eac91da00909c7d7c18d3287347c.verbs, 1), ImPre_BIT, (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00));
    }
    o_59f5b47a3f90cc3b7bab04c6d937b75a8(*(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00)) == o_af5b47a3f90dc3b7bab04c6d937b75a8);
    t_form o_054483c612d9c7180bcd4664072a612d = {
        .word = L"\x6F"
                L"u\040Q\x75"
                L"e\156t\x69"
                L"n\054 \x41"
                L"x\145l\x20"
                L"e\164 \x50"
                L"a\165l",
        .tag = (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00),
        .next = o_af5b47a3f90dc3b7bab04c6d937b75a8,
    };
    *(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000002 + 0x0000000000000201 + 0x0000000000000801 - 0x0000000000000A03)) = &o_054483c612d9c7180bcd4664072a612d;
    o_49f5b47a3f90cc3b7bab04c6d937b75a8
    {
        *(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000004 + 0x0000000000000202 + 0x0000000000000802 - 0x0000000000000A06)) = o_bz5b47a3f90cc3b7bab04c6d937b75a8(getRandomWord(o_5357eac91da00909c7d7c18d3287347c.verbs, (0x0000000000000002 + 0x0000000000000201 + 0x0000000000000801 - 0x0000000000000A03)), P3_BIT + PL_BIT + IFut_BIT, (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00));
    }
    o_59f5b47a3f90cc3b7bab04c6d937b75a8(*(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000004 + 0x0000000000000202 + 0x0000000000000802 - 0x0000000000000A06)) == o_af5b47a3f90dc3b7bab04c6d937b75a8);
    o_49f5b47a3f90cc3b7bab04c6d937b75a8
    {
        *(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000006 + 0x0000000000000203 + 0x0000000000000803 - 0x0000000000000A09)) = o_bz5b47a3f90cc3b7bab04c6d937b75a8(getRandomWord(o_5357eac91da00909c7d7c18d3287347c.adverbs, (0x0000000000000002 + 0x0000000000000201 + 0x0000000000000801 - 0x0000000000000A03)), (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00), (0x0000000000000000 + 0x0000000000000300 + 0x0000000000000800 - 0x0000000000000B00));
    }
    o_59f5b47a3f90cc3b7bab04c6d937b75a8(*(o_f9c4fad3b5e738b92096dd165dad3b5b + (0x0000000000000006 + 0x0000000000000203 + 0x0000000000000803 - 0x0000000000000A09)) == o_af5b47a3f90dc3b7bab04c6d937b75a8);
    wchar_t *o_3ffe184342801d4337794ec0d2333d2d = o_2f5b67a3f90cc3b7bab04c6d937b75a8((0x00000000000000C8 + 0x0000000000000264 + 0x0000000000000864 - 0x0000000000000B2C), o_0gf5b47a3f90cc3b7bab04c6d937b75a8(wchar_t));
    o_69f5b47a3f90cc3b7bab04c6d937b75a8(o_62f5b47a3f90cc3b7bab04c6d937b75a8 o_25bbf0c7d99cf5e2d2bbac6719f0afe5 = 0; o_25bbf0c7d99cf5e2d2bbac6719f0afe5 < (0x0000000000000008 + 0x0000000000000204 + 0x0000000000000804 - 0x0000000000000A0C); o_25bbf0c7d99cf5e2d2bbac6719f0afe5++)
    {
        o_3ffe184342801d4337794ec0d2333d2d = wcscat(o_3ffe184342801d4337794ec0d2333d2d, (*(o_f9c4fad3b5e738b92096dd165dad3b5b + o_25bbf0c7d99cf5e2d2bbac6719f0afe5))->word);
        o_3ffe184342801d4337794ec0d2333d2d = wcscat(o_3ffe184342801d4337794ec0d2333d2d, L"\x20"
                                                                                        "");
    }
    o_3ffe184342801d4337794ec0d2333d2d = wcscat(o_3ffe184342801d4337794ec0d2333d2d, L"\x2E"
                                                                                    "");
    wprintf(L"\x25"
            "l\163\x0A",
            o_azf5b47a3f90cc3b7bab04c6d937b75a8(o_3ffe184342801d4337794ec0d2333d2d));
    o_22f963af3a82075f9fe12614af395e64(o_3ffe184342801d4337794ec0d2333d2d);
    o_86625afd559ad8fb8d6241793615b5fd();
    o_99f5b47a3f90cc3b7bab04c6d937b75a8;
};
;