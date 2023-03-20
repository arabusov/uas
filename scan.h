/*
 * Lexer for x86 16 bit UNIX assembler
 *
 * Author: Andrei Rabusov <arabusov@gmail.com>
 *         2022-10-22
 */

#ifndef _LEX_
#define _LEX_

#define UNKNOWN_TOKEN   -1

#define OPCODE_MACRO \
    MOVB, MOVW,\
    ADDB, ADDW

enum reg8 {
    R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH
};

enum reg16 {
    R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI
};

enum sreg {
    R_ES, R_CS, R_SS, R_DS
};

enum token {
    UNKNOWN         =  -1,
    IDENT           = 256,        /* Skip first 256 values for ASCII */
    OCT,
    DEC,
    HEX,
    REG,
    OPCODE
};

extern enum token nextok (void);
#endif /* _LEX_ */
