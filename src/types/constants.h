/*DiCtionary
Quentin Cardona, Axel Loones and Paul Mairesse
This file contains the constants and define*/
#ifndef verb_h
#define verb_h

// string constants
#define VERB_TYPE L"Ver"
#define NOUN_TYPE L"Nom"
#define ADJECTIVE_TYPE L"Adj"
#define ADVERB_TYPE L"Adv"
#define PRONOUN_TYPE L"Pro"
#define DETERMINANTS_TYPE L"Det"

#define SG L"SG"
#define PL L"PL"

#define P1 L"P1"
#define P2 L"P2"
#define P3 L"P3"

#define IPre L"IPre"
#define IImp L"IImp"
#define SPre L"SPre"
#define IPSim L"IPSim"
#define PPre L"PPre"
#define SImp L"SImp"
#define PPas L"PPas"
#define IFut L"IFut"
#define CPre L"CPre"
#define Inf L"Inf"

#define Mas L"Mas"
#define Fem L"Fem"
#define InvGen L"InvGen"
#define InvPL L"InvPL"

#define ANSI_COLOR_RED L"\x1b[0m\x1b[31;4m"
#define ANSI_COLOR_GREEN L"\x1b[0m\x1b[32;1;3m"
#define ANSI_COLOR_YELLOW L"\x1b[0m\x1b[33m"
#define ANSI_COLOR_BLUE L"\x1b[0m\x1b[34m"
#define ANSI_COLOR_MAGENTA L"\x1b[0m\x1b[35m"
#define ANSI_COLOR_CYAN L"\x1b[0m\x1b[36m"
#define ANSI_COLOR_RESET L"\x1b[0m"
#define ANSI_BACKGROUND_WHITE L"\x1b[0m\x1b[39;1m\e[47m\e[K"

// binary constants
#define SG_BIT 1
#define PL_BIT 2

#define P1_BIT 4
#define P2_BIT 8
#define P3_BIT 16

#define IPre_BIT 32
#define IImp_BIT 64
#define SPre_BIT 128
#define IPSim_BIT 256
#define PPre_BIT 512
#define SImp_BIT 1024
#define PPas_BIT 2048
#define IFut_BIT 4096
#define CPre_BIT 8192
#define Inf_BIT 16384

#define Mas_BIT 32768
#define Fem_BIT 65536
#define InvGen_BIT Mas_BIT + Fem_BIT
#define InvPL_BIT PL_BIT + SG_BIT

#define Main_BIT 524288

#endif