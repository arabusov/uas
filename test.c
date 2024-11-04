/*
 * Temporary int main (void) file for tests
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#include <stdio.h>
#include "scan.h"
#include "buf.h"

int main (void)
{
        int buf_sta;
        do {
                enum token tok;
                buf_sta = read_buf();
                printf("%s", buf);
                do {
                        char *sym;
                        printf("pos = %d,", (int)(bp-buf));
                        tok = nextok(&sym);
                        printf(" token = %d", tok);
                        printf(" sym = %s\n", sym);
                } while ((int)tok > 0);
        } while (buf_sta);
        return 0;
}
