/*
 * Symbol table and symbol subroutines
 *
 * Author:      Andrei Rabusov <arabusov@gmail.com>
 * Changelog:   2023-03-20  File created
 */

#include "sym.h"

struct symbol   symtab[SYMTAB_LEN];
stuct symbol    sp = symtab;

extern int eost(void)
{
        return (sp - symtab) >= SYMTAB_LEN;
}

extern void init_symtab(void)
{
        int i;
        for (i = 0; i < SYMTAB_LEN; i++) {
                symtab.type = NO_SYMBOL;
        }
}

