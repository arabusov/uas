%token OP REG SYSREG REG8 IMMED ADDR LAB COL LPAR RPAR COM
%%
statement   : LAB cmd '\n'
            | cmd '\n'

cmd         : OP
            | OP arg
            | OP arg COM arg
            | OP arg COM arg COM arg

arg         : REG
            | IMMED
            | ADDR
            | modrm

modrm       : SYSREG COL default_modrm
            | default_modrm

default_modrm
            : LPAR REG COM REG RPAR
            | LPAR REG COM RPAR
            | LPAR COM REG RPAR
%%
