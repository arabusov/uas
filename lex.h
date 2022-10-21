#ifndef _LEX_
#define _LEX_

#define UNKNOWN_TOKEN   -1
#define NOOCT           -2
#define NODEC           -2
#define NOHEX           -3

#define OPCODE_MACRO \
    MOVB, MOVW,\
    ADDB, ADDW

typedef enum {
    ENDL,
    COMMA,
    COLON,
    SEMICOLON,
    SHARP,
    BRA,
    KET,
    DOL,
    R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH,
    R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI,
    R_ES, R_CS, R_SS, R_DS,
    OPCODE_MACRO,
    IDENT,
    OCT,
    DEC,
    HEX
} token_t;

extern token_t next_tok (void);
#endif /* _LEX_ */
