/*
 * Temporary int main (void) file for tests
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#include "lex.h"
#include "buf.h"
#include <stdio.h>
#define str(x) #x
#define xstr(x) str(x)

int main (void)
{
    int buf_sta;
    do {
        token_t tok;
        buf_sta = read_buf ();
        puts (buf);
        do {
            printf ("pos = %d,", (int)(bp-buf));
            tok = next_tok ();
            printf (" token = %d\n", tok);
        } while ((int)tok > 0);
    } while (buf_sta);
    return 0;
}
