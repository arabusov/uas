/*
 * Buffer for x86 16 bit UNIX assembler
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#include "buf.h"
#include <stdio.h>
#include <string.h>

char buf[N_BUF];
char *bp = buf;

extern int read_buf (void)
{
    int ch;
    memset (buf, 0, N_BUF);
    bp = buf;
    while ((ch = getchar ()) != EOF) {
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
