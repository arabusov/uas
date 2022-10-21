/*
 * Lexer for x86 16 bit UNIX assembler
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

/*
 * C&P from a wikibook on gas
 * seg:disp(base reg, index reg, scale factor)
 * label: movb $0x05, %al
 * seg:disp(base reg, index reg, scale factor)
 */
#include <stdio.h>
#include <string.h>
#include "lex.h"
#include "buf.h"

token_t ident (char **p)
{
    if (    (**p >= 'a' && **p <= 'z') ||
            (**p >= 'A' && **p <= 'Z') ||
            **p == '_')
        (*p)++;
    else
        return 0;
    while ( (**p >= 'a' && **p <= 'z') ||
            (**p >= 'A' && **p <= 'Z') ||
            (**p >= '0' && **p <= '9') ||
            **p == '_')
        (*p)++;
    return IDENT;
}

int is_wp (char ch)
{
    return (ch == ' ') || (ch == '\t');
}

void skip_wsp (void)
{
    while (is_wp (*bp)) bp++;
}

token_t opc (char **p)
{
    if (is_wp ((*p)[4])) {
        char ch = (*p)[4];
        (*p)[4] = '\0';
        if (strcmp (*p, "movb") == 0) { (*p) +=4; return **p = ch, MOVB; }
        if (strcmp (*p, "movw") == 0) { (*p) +=4; return **p = ch, MOVW; }
        if (strcmp (*p, "addb") == 0) { (*p) +=4; return **p = ch, ADDB; }
        if (strcmp (*p, "addw") == 0) { (*p) +=4; return **p = ch, ADDW; }
    }
    return 0;
}

#define GENREG_MACRO(ch, r16, r8l, r8h)\
    if (**p == ch) {\
        if ((*p)[1] == 'x') \
            return *p+=2, r16; \
        else if ((*p)[1] == 'l') \
            return *p+=2, r8l; \
        else if ((*p)[1] == 'h') \
            return *p+=2, r8h; \
    }

token_t reg (char **p)
{
    GENREG_MACRO ('a', R_AX, R_AL, R_AH)
    GENREG_MACRO ('c', R_CX, R_CL, R_CH)
    GENREG_MACRO ('d', R_DX, R_DL, R_DH)
    GENREG_MACRO ('b', R_BX, R_BL, R_BH)
    if (**p == 'e' && (*p)[1] == 's') return (*p)+=2, R_ES;
    if (**p == 'd' && (*p)[1] == 's') return (*p)+=2, R_DS;
    if (**p == 's' && (*p)[1] == 's') return (*p)+=2, R_SS;
    if (**p == 'c' && (*p)[1] == 's') return (*p)+=2, R_CS;
    if (**p == 's' && (*p)[1] == 'i') return (*p)+=2, R_SI;
    if (**p == 'd' && (*p)[1] == 'i') return (*p)+=2, R_DI;
    if (**p == 'b' && (*p)[1] == 'p') return (*p)+=2, R_BP;
    if (**p == 's' && (*p)[1] == 'p') return (*p)+=2, R_SP;
    return 0;
}

int is_lat (char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

token_t oct (char **p)
{
    while (**p >= '0' && **p <= '7') (*p)++;
    if (is_lat (**p))
        return OCT;
    return NOOCT;
}

token_t dec (char **p)
{
    while (**p >= '0' && **p <= '9') (*p)++;
    if (!is_lat (**p))
        return DEC;
    return NODEC;
}

token_t hex (char **p)
{
    while ( (**p >= '0' && **p <= '9') ||
            (**p >= 'a' && **p <= 'f')) (*p)++;
    if (is_lat (**p))
        return HEX;
    return NOHEX;
}

extern token_t next_tok (void)
{
    token_t tmp;
    skip_wsp ();
    switch (*bp) {
    case '\n':  return bp++, ENDL;
    case ',':   return bp++, COMMA;
    case ':':   return bp++, COLON;
    case ';':   return bp++, SEMICOLON;
    case '#':   return bp++, SHARP;
    case '(':   return bp++, BRA;
    case ')':   return bp++, KET;
    case '$':   return bp++, DOL;
    case '%':   return bp++, reg (&bp);
    case '0':   if (*++bp == 'x')
                    return bp++, hex (&bp);
                else
                    return oct (&bp);
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
                return bp++, dec (&bp);
    }
    tmp = opc (&bp);
    if (tmp) {
        return tmp;
    }
    tmp = ident (&bp);
    if (tmp) {
        return tmp;
    }
    return UNKNOWN_TOKEN;
}
