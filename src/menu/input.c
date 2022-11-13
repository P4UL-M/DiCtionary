#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../functions/dictionary.h"
#include "../functions/search.h"
#include "../types/struct.h"
#ifdef _WIN32
#include <conio.h>
#define getKey()        \
    ({                  \
        return getch(); \
    })
#else
#include <termios.h>
#include <unistd.h>
#define getKey()                                       \
    ({                                                 \
        char c = 0;                                    \
        static struct termios oldTermios, newTermios;  \
        tcgetattr(STDIN_FILENO, &oldTermios);          \
        newTermios = oldTermios;                       \
        cfmakeraw(&newTermios);                        \
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios); \
        c = getchar();                                 \
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios); \
        fflush(stdin);                                 \
        return c;                                      \
    })
#endif
#define AUTOCOMPLETION 0
#define STOP 1
#define CONTINUE 2

char getKeyFunc()
{
    getKey();
}

char *scanAutoCompletion(t_dictionary dictionnary, char *target, int type)
{
    int i = 0, state = CONTINUE;
    while (state != STOP)
    {
        while (state == CONTINUE)
        {
            char c = getKeyFunc();
            if (c == '\t')
            {
                printf("\n");
                state = AUTOCOMPLETION;
            }
            else if (c == '\n' || c == 13)
            {
                printf("\n");
                state = STOP;
            }
            else if (c == 127)
            {
                if (i > 0)
                {
                    target[--i] = '\0';
                    printf("\b \b");
                }
            }
            else
            {
                target[i] = c;
                printf("%c", c);
                i++;
            }
        }
        target[i] = '\0';
        if (state == AUTOCOMPLETION)
        {
            p_fpile pile = createEmptyFPile();
            switch (type)
            {
            case 1:
                autocompletion(dictionnary.nouns, target, pile);
                break;
            case 2:
                autocompletion(dictionnary.verbs, target, pile);
                break;
            case 3:
                autocompletion(dictionnary.adjectives, target, pile);
                break;
            case 4:
                autocompletion(dictionnary.adverbs, target, pile);
                break;
            default:
                autocompletion(dictionnary.nouns, target, pile);
                autocompletion(dictionnary.verbs, target, pile);
                autocompletion(dictionnary.adjectives, target, pile);
                autocompletion(dictionnary.adverbs, target, pile);
                break;
            }
            if (pile->size == 0)
            {
                printf("No word found\n");
            }
            else if (pile->size > 10)
            {
                printf("Too many words found, please be more specific\n");
            }
            else
            {
                printf("Words found:\n");
                displayFPile(pile);
            }
            freeFPile(pile);
            state = CONTINUE;
            printf(">%s", target);
        }
    }
    printf("the word is : %s\n", target);
    return target;
}

// char *autocompletion(p_tree tree)
// {
//     char *word = (char *)malloc(sizeof(char) * 100);
//     int i = 0, continuing = 1;
//     char c;
//     while ((c = getchar()) != '\n' && continuing)
//     {
//         if (c == '\t')
//         {
//             continuing = 0;
//             word[i] = '\0';
//         }
//         else
//         {
//             word[i] = c;
//             i++;
//         }
//     }
//     if (c == '\t')
//     {
//         printf("%s\n", word);
//     }
//     p_fpile pile = completion(tree, word);
//     if (pile != NULL)
//     {
//         p_form temp = pile->head;
//         while (temp != NULL)
//         {
//             printf("%s", temp->word);
//             displayFPile(pile);
//             temp = depileForm(pile);
//         }
//         return word;
//     }
//     else
//         printf("Autocompletion impossible\n");
// }