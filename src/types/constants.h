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
#define SG_BIT 1
#define PL_BIT 2

#define P1_BIT 4
#define P2_BIT 8
#define P3_BIT 16

#define IPre_BIT 32
#define IImp_BIT 64
#define SPre_BIT 128
#define IPsimp_BIT 256
#define PPre_BIT 512
#define SImp_BIT 1024
#define PPas_BIT 2048
#define IFut_BIT 4096
#define CPre_BIT 8192
#define Inf_BIT 16384

#define Mas_BIT 32768
#define Fem_BIT 65536

#define Main_BIT 131072

unsigned int get_bit(char *str);

#endif