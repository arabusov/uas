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

#define DIR_MACRO \
        DB_BYTE

#define REG8_MACRO \
    R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH

#define REG16_MACRO \
    R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI

#define SREG_MACRO \
    R_ES, R_CS, R_SS, R_DS

enum token {
    UNKNOWN         =  -1,
    IDENT           = 256,        /* Skip first 256 values for ASCII */
    OCT,
    DEC,
    HEX,
    REG16_MACRO,
    REG8_MACRO,
    SREG_MACRO,
    OPCODE_MACRO,
    DIR_MACRO,
    COMMENT
};

extern enum token nextok (char **);
#endif /* _LEX_ */
