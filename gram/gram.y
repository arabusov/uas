%token OP REG SYSREG REG8 IMMED CIMMED DISP CDISP LAB COL LPAR RPAR COM NL
%%
statement   : LAB cmd
            | cmd

cmd         : OP
            | OP arg
            | OP arg COM arg
            | OP arg COM arg COM arg

arg         : REG
            | IMMED
            | CIMMED
            | DISP
            | CDISP
            | modrm

modrm       : SYSREG COL default_modrm
            | direct_modrm
direct_modrm: DISP default_modrm
            | CDISP default_modrm

default_modrm
            : LPAR REG COM REG RPAR
            | LPAR REG COM RPAR
            | LPAR COM REG RPAR
%%

#include <stdio.h>

extern char yytext[];
extern int column;

int main(void)
{
    return yyparse();
}

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
