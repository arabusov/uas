/*
 * Header defines the symbol union and the symbol table
 *
 * Author:      Andrei Rabusov <arabusov@gmail.com>
 * Changelog:   2023-03-20  File created
 */

#ifndef _SYM_H_
#define _SYM_H_

#define IDENT_LEN       16
#define SYMTAB_LEN      1024

struct symbol
{
        enum {
                NO_SYMBOL,
                INT_LITERAL,
                STR_LITERAL,
                IDENT
        } type;
        union {
                int     int_lit;
                char    *str_lit;
                char    ident[IDENT_LEN];
        } val;
};

extern struct symbol    symtab[SYMTAB_LEN];
extern struct symbol    *sp;

extern void             init_symtab(void);
extern int              eost(void);

#endif /* _SYM_H_ */

