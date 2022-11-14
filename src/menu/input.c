#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../functions/dictionary.h"
#include "../functions/search.h"
#include "../types/struct.h"
#ifdef _WIN32
#include <conio.h>
#define getKey()                                             \
    ({                                                       \
        wchar_t *c = (wchar_t *)malloc(sizeof(wchar_t) * 2); \
        c[0] = (wchar_t)_getwch();                           \
        c[1] = '\0';                                         \
        fflush(stdin);                                       \
        return c;                                            \
    })
#else
#include <termios.h>
#include <unistd.h>
#define getKey()                                             \
    ({                                                       \
        wchar_t *c = (wchar_t *)malloc(sizeof(wchar_t) * 3); \
        static struct termios oldTermios, newTermios;        \
        tcgetattr(STDIN_FILENO, &oldTermios);                \
        newTermios = oldTermios;                             \
        cfmakeraw(&newTermios);                              \
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);       \
        c[0] = (wchar_t)getwchar();                          \
        c[1] = '\0';                                         \
        if (c[0] == 195)                                     \
            c[1] = (wchar_t)getwchar();                      \
        else                                                 \
            c[1] = '\0';                                     \
        c[2] = '\0';                                         \
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);       \
        fflush(stdin);                                       \
        return c;                                            \
    })
#endif
#define AUTOCOMPLETION 0
#define STOP 1
#define CONTINUE 2

wchar_t *getKeyFunc()
{
    getKey();
}

wchar_t *scanAutoCompletion(t_dictionary dictionnary, wchar_t *target, int type)
{
    int i = 0, state = CONTINUE;
    while (state != STOP)
    {
        while (state == CONTINUE)
        {
            wchar_t *c = getKeyFunc();
            if (c[0] == '\t')
            {
                wprintf(L"\n");
                state = AUTOCOMPLETION;
            }
            else if (c[0] == '\n' || c[0] == 13)
            {
                wprintf(L"\n");
                state = STOP;
            }
            else if (c[0] == 127 || c[0] == '\b')
            {
                if (i > 0)
                {
                    target[--i] = '\0';
                    wprintf(L"\b \b");
                }
            }
            else
            {
                wprintf(L"%ls", c);
                for (int j = 0; j < wcslen(c); j++)
                {
                    target[i++] = c[j];
                }
            }
        }
        target[i] = L'\0';
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
                wprintf(L"No word found\n");
            }
            else if (pile->size > 10)
            {
                wprintf(L"Too many words found, please be more specific\n");
            }
            else
            {
                wprintf(L"Words found:\n");
                displayFPile(pile);
            }
            freeFPile(pile);
            state = CONTINUE;
            wprintf(L">%ls", target);
        }
    }
    return target;
}