%token OP REG SYSREG REG8 IMMED CIMMED IDENT CDISP COL LPAR RPAR COM NL
%%

statements  : statements statement
            | statement

statement   : IDENT COL instr NL
            | instr NL

instr       : OP operands
            | OP

operands    : arg
            | arg COM arg

arg         : reg
            | IMMED
            | CIMMED
            | IDENT 
            | CDISP
            | modrm

reg         : REG
            | REG8
            | SYSREG

modrm       : SYSREG COL default_modrm
            | default_modrm

default_modrm
            : IDENT direct_modrm
            | CDISP direct_modrm

direct_modrm
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
