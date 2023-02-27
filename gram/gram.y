%token OP REG SYSREG REG8 IDENT CONST LPAR RPAR
%%

statements  : statements statement
            | statement
            ;

statement   : IDENT ':' instr '\n'
            | instr '\n'
            ;

instr       : OP operands
            | OP
            ;

operands    : arg
            | arg ',' arg
            ;

arg         : reg
            | immediate
            | disp
            | modrm
            ;

immediate   : '$' disp
            ;

disp        : IDENT
            | CONST
            | '(' expr ')'
            ;

unary_expr  :
            | disp
	        | '~' unary_expr
	        ;

mul_expr    : unary_expr
            | mul_expr '*' unary_expr
	        | mul_expr '/' unary_expr
	        | mul_expr '%' unary_expr
	        ;

add_expr    : mul_expr
            | add_expr '+' mul_expr
            | add_expr '-' mul_expr
            ;
and_expr    : add_expr
	        | and_expr '&' add_expr
	        ;

xor_expr    : and_expr
            | xor_expr '^' and_expr
            ;

or_expr     : xor_expr
	        | or_expr '|' xor_expr
	        ;

expr        : or_expr
            ;

reg         : REG
            | REG8
            | SYSREG
            ;

modrm       : SYSREG ':' default_modrm
            | default_modrm
            ;

default_modrm
            : disp direct_modrm
            ;

direct_modrm
            : '(' REG ',' REG ')'
            | '(' REG ',' ')'
            | '(' ',' REG ')'
            ;
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
