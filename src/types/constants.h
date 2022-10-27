/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the constants and define*/
#ifndef verb_h
#define verb_h

// string constants
#define VERB_TYPE "Ver"
#define NOUN_TYPE "Nom"
#define ADJECTIVE_TYPE "Adj"
#define ADVERB_TYPE "Adv"

#define SG "SG"
#define PL "PL"

#define P1 "P1"
#define P2 "P2"
#define P3 "P3"

#define IPre "IPre"
#define IImp "IImp"
#define SPre "SPre"
#define IPsimp "IPsimp"
#define PPre "PPre"
#define SImp "SImp"
#define PPas "PPas"
#define IFut "IFut"
#define CPre "CPre"
#define Inf "Inf"

#define Mas "Mas"
#define Fem "Fem"

#define ANSI_COLOR_RED "\x1b[0m\x1b[31;4m"
#define ANSI_COLOR_GREEN "\x1b[0m\x1b[32;1;3m"
#define ANSI_COLOR_YELLOW "\x1b[0m\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[0m\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[0m\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[0m\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_BACKGROUND_WHITE "\x1b[0m\x1b[39;1m\e[47m\e[K"

// binary constants
#define SG_BIT b '0x1'
#define PL_BIT b '0x2'

#define P1_BIT b '0x4'
#define P2_BIT b '0x8'
#define P3_BIT b '0x10'

#define IPre_BIT b '0x20'
#define IImp_BIT b '0x40'
#define SPre_BIT b '0x80'
#define IPsimp_BIT b '0x100'
#define PPre_BIT b '0x200'
#define SImp_BIT b '0x400'
#define PPas_BIT b 'Ox800'
#define IFut_BIT b '0x1000'
#define CPre_BIT b '0x2000'
#define Inf_BIT b '0x4000'

#define Mas_BIT b '0x4'
#define Fem_BIT b '0x8'

unsigned int get_bit(char *str);

#endif