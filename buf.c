/*
 * Buffer for x86 16 bit UNIX assembler
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#include <stdio.h>
#include <string.h>

#include "buf.h"

char buf[N_BUF + 2]; /* Extra two symbols just in case */
char *bp = buf;

/* In assembler, buffer stops at the EOL or EOF */
extern int read_buf(void)
{
        int ch;
        memset(buf, 0, N_BUF);
        bp = buf;
        while ((ch = getchar()) != EOF) {
                if (ch != '\n' && (bp - buf) < N_BUF)
                        *bp++ = ch;
                else
                        break;
        }
        if (ch == '\n')
                *bp = '\n';
        bp = buf;
        return ch == '\n' ? 1 : 0;
}

/* End of buffer */
extern int eob(char *p)
{
        return (p - buf) >= N_BUF;
}

