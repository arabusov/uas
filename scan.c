/*
 * Scaner for x86 16 bit UNIX assembler
 *
 * Author:      Andrei Rabusov <arabusov@gmail.com>
 * Changelog:   2023-03-20  Remove redundant parts of the scanner
 *              2022-10-22  Create scanner
 */

#include <stdio.h>
#include <string.h>
#include "scan.h"
#include "buf.h"

/* Returns true if character ch is from the latin alphabet. Assume ASCII */
static int is_lat(char ch)
{
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

/* Returns true if character ch is either from the latin alph or '_' */
static int is_lou(char ch)
{
        return is_lat || ch == '_';
}

/* Checks if *p points to an identifier, returns 0 if not */
static enum token ident(char **p, char **symb)
{
        char *start = *p;
        if (eob(*p)) /* This should not happen */
                return UNKNOWN;
        if (is_lou(*p))
                (*p)++;
        while (is_lou(*p) || is_digit(*p)) { 
                (*p)++;
        }
        return IDENT;
}

/* Is whitespace? */
static int is_wp(char ch)
{
        return (ch == ' ') || (ch == '\t');
}

/*
 * Increments buffer pointer to find first not whitespace
 */
static void skip_wsp(void)
{
        while (is_wp (*bp)) bp++;
}

/*
 * Hardcoded opcode table
 */
static enum token opc(char **p)
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

/*
 * Macro for generic registers, includes 16- and 8-bit variants
 */
#define GENREG_MACRO(ch, r16, r8l, r8h)\
        if (**p == ch) {\
                if ((*p)[1] == 'x') \
                return *p+=2, r16; \
                else if ((*p)[1] == 'l') \
                return *p+=2, r8l; \
                else if ((*p)[1] == 'h') \
                return *p+=2, r8h; \
        }

/* Returns register token */
static enum token reg(char **p)
{
        GENREG_MACRO ('a', R_AX, R_AL, R_AH);
        GENREG_MACRO ('c', R_CX, R_CL, R_CH);
        GENREG_MACRO ('d', R_DX, R_DL, R_DH);
        GENREG_MACRO ('b', R_BX, R_BL, R_BH);
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

/* Check if octal literal */
static enum token oct(char **p)
{
        while (**p >= '0' && **p <= '7') {
                (*p)++;
        }
        if (is_lou(**p))
                return OCT;
        return UNKNOWN;
}

/* Check if decimal literal */
static enum token dec(char **p)
{
        while (**p >= '0' && **p <= '9') {
                (*p)++;
        }
        if (!is_lou (**p))
                return DEC;
        return UNKNOWN;
}

/* Check if hexadecimal literal */
static enum token hex(char **p)
{
        while ((**p >= '0' && **p <= '9') || (**p >= 'a' && **p <= 'f')) {
                (*p)++;
        }
        return UNKNOWN;
}

/* Returns next token */
extern enum token nextok(char **sym)
{
        enum token tmp;
        if (is_eof)
                return EOF;
        skip_wsp();
        skip_comment();
        /* Default assumption: no symbol is associated with tok */
        *sym = NULL;
        /* If literal begins with nonzero, it is decimal */
        if (*bp >= '1' && *bp <= '9')
                return dec(&bp);
        if (bp == 0 && *bp == '#')
                return pre_dir(&bp);
        switch (*bp) {
                case EOF:       is_eof = 1; return EOF;
                case '#':       return 
                case '%':       return bp++, reg(&bp);
                case '.':       return bp++, directive(&bp);
                case '0':       if (*++bp == 'x')
                                        return bp += 2, hex(&bp);
                                else
                                        return oct(&bp);
        }
        tmp = opc(&bp);
        if (tmp) {
                return tmp;
        }
        tmp = ident (&bp);
        if (tmp) {
                return tmp;
        }
        return *bp++;
}