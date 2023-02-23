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
#define W(T)    printf("tok %d {", (T)); ECHO; printf("} "); return (T);
%}
%%
"# "{DEC}" "{FNAME}{CPPFL}*"\n"  {    printf("cpp %s\n", yytext); }

mov{ARGT}   |
add{ARGT}   |
sub{ARGT}   |
cmp{ARGT}   |
push        |
pop         |
hlt         {   count(); W(OP); }

\%ax        |
\%bx        |
\%cx        |
\%dx        |
\%si        |
\%di        |
\%sp        |
\%bp        {   count(); W(REG); }
\%cs        |
\%ds        |
\%ss        |
\%es        {   count(); W(SYSREG); } 
\%al        |
\%bl        |
\%cl        |
\%dl        |
\%ah        |
\%bh        |
\%ch        |
\%dh        {   count(); W(REG8); }

,           {   count(); W(COM); }
"\n"        {   count(); W(NL); }

"("         {   count(); W(LPAR); }

")"         {   count(); W(RPAR); }

\$[ \t]*{ID}    {   count(); W(IMMED); }
\$[ \t]*{DEC}   |
\$[ \t]*{HEX}   {   count(); W(CIMMED); }

^[ \t]*{ID}[ \t]*":"  {   count(); W(LAB); }

{ID}        {   count(); W(DISP); }
{DEC}       |
{HEX}       {   count(); W(CDISP); }

:           {   count(); W(COL); }

;.*
!.*
#.*

[ \t\v\f]   {   count(); }

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

}
