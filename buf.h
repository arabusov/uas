/*
 * Buffer for x86 16 bit UNIX assembler
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#ifndef _BUF_
#define _BUF_

#define N_BUF   512
extern char     buf[N_BUF+2];
extern char     *bp;
extern int      is_eof;

extern int      read_buf(void);
extern int      eob(char *p);

#endif /* _BUF_ */
