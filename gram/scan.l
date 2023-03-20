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
#define W(T)  ECHO; return (T);
%}
%%
"# "{DEC}" "{FNAME}{CPPFL}*"\n"  {    printf("cpp %s\n", yytext); }

mov{ARGT}   |
add{ARGT}   |
sub{ARGT}   |
cmp{ARGT}   |
push        |
pop         |
hlt         {   count(); W(OP);     }

\%[a-d]x    |
\%[sd]i     |
\%[sb]p     {   count(); W(REG);    }
\%[cdse]s   {   count(); W(SYSREG); }
\%[a-d][lh] {   count(); W(REG8);   }

,           {   count(); W(',');    }
"\n"        {   count(); W('\n');   }
"("         {   count(); W('(');    }
")"         {   count(); W(')');    }
"$"         {   count(); W('$');    }
":"         {   count(); W(':');    }
\+         {   count(); W('+');    }
\*         {   count(); W('*');    }
\/         {   count(); W('/');    }

{ID}        {   count(); W(IDENT);  }
{DEC}       |
{HEX}       {   count(); W(CONST);  }


;.*
!.*

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
