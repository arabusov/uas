%token OP REG SYSREG REG8 IMED CIMED DIRECT CDIRECT LAB COL LPAR RPAR COM
%%
statement   : LAB cmd '\n'
            | cmd '\n'

cmd         : OP
            | OP arg
            | OP arg COM arg
            | OP arg COM arg COM arg

arg         : REG
            | IMED
            | CIMED
            | DIRECT
            | CDIRECT
            | modrm

modrm       : SYSREG COL default_modrm
            | direct_modrm
direct_modrm: DIRECT default_modrm
            | CDIRECT default_modrm

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
    yyparse();
}

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
