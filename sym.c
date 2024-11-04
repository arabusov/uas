/*
 * Symbol table and symbol subroutines
 *
 * Author:      Andrei Rabusov <arabusov@gmail.com>
 * Changelog:   2023-03-20  File created
 */

#include <stdio.h>
#include "sym.h"

struct symbol   symtab[SYMTAB_LEN];
struct symbol   *sp = symtab;

extern int eost(void)
{
        return (sp - symtab) >= SYMTAB_LEN;
}

extern void init_symtab(void)
{
        int i;
        for (i = 0; i < SYMTAB_LEN; i++) {
                symtab[i].type = NO_SYMBOL;
        }
}

extern void print_symbol(struct symbol *s)
{
        switch (s->type) {
                case NO_SYMBOL:   printf("NO_SYMB");
                                  break;
                case INT_LITERAL: printf("INT_LIT:%d", s->val.int_lit);
                                  break;
                case STR_LITERAL: printf("STR_LIT:%s", s->val.str_lit);
                                  break;
                case IDENT:       printf("IDENT:%s", s->val.ident);
                                  break;
        }
}

static struct symbol *hash_tab[SYMTAB_LEN];

int hash(char *s)
{
        int hash_val = 0;
        for (hash_val = 0; *s != '\0'; ) {
                hash_val += *s++;
        }
        return hash_val % SYMTAB_LEN;
}

struct symbol *lookup(char *s)
{
        struct symbol *np;
        for (np = hash_tab[hash(s)]; np < SYMTAB_LEN + sp;
                        np = (np++) % SYMTAB_LEN) {
        }
}
