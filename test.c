/*
 * Temporary int main (void) file for tests
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#include <stdio.h>
#include "scan.h"
#include "buf.h"
#include "sym.h"

int main (void)
{
        int buf_sta;
        init_symtab();
        do {
                struct symbol sym;
                token_t tok;
                buf_sta = read_buf ();
                puts (buf);
                do {
                        printf("pos = %d,", (int)(bp-buf));
                        tok = next_tok(sym);
                        printf(" token = %d", tok);
                        if (symbol.type != NO_SYMBOL) {
                                printf(", sym = ");
                                print_symbol(symbol);
                                printf("\n");
                        }
                } while ((int)tok > 0);
        } while (buf_sta);
        return 0;
}
