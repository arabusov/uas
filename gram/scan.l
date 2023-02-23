ID      [a-zA-Z][a-zA-Z0-9]*
ARGT    [bw]
DEC     [0-9]+
HEX     "0x"[0-9a-fA-F]+
CPPFL   " "[1-4]
FNAME   [a-zA-Z0-9\/\.]+
%{
#include "y.tab.h"
int column=0;
void count();
%}
%%
"# "{DEC}" "{FNAME}{CPPFL}*"\n"  {    printf("cpp %s\n", yytext); }

mov{ARGT}   |
add{ARGT}   |
sub{ARGT}   |
cmp{ARGT}   |
push        |
pop         |
hlt         {   count(); return OP; }

\%ax        |
\%bx        |
\%cx        |
\%dx        |
\%si        |
\%di        |
\%sp        |
\%bp        {   count(); return REG;}
\%cs        |
\%ds        |
\%ss        |
\%es        {   count(); return SYSREG;; } 
\%al        |
\%bl        |
\%cl        |
\%dl        |
\%ah        |
\%bh        |
\%ch        |
\%dh        {   count(); return REG8; }

,           {   count(); return COM; }

"("         {   count(); return LPAR; }

")"         {   count(); return RPAR; }

\$[ \t]*{ID}    {   count(); return IMED; }
\$[ \t]*{DEC}   |
\$[ \t]*{HEX}   {   count(); return CIMED; }

^[ \t]*{ID}[ \t]*":"  {   count(); return LAB; }

{ID}        {   count(); return DIRECT; }
{DEC}       |
{HEX}       {   count(); return CDIRECT; }

:           {   count(); return COL; }

;.*
!.*
#.*

[ \t\v\n\f] {   count(); }

.           {   printf("scan error %d %s\n", column, yytext); }

%%

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}
