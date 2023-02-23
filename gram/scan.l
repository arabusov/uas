ID      [a-zA-Z][a-zA-Z0-9]*
ARGT    [bw]
DEC     [0-9]+
HEX     "0x"[0-9a-fA-F]+
CPPFL   " "[1-4]
FNAME   [a-zA-Z0-9\/\.]+
%%
"# "{DEC}" "{FNAME}{CPPFL}*"\n"  {    printf("cpp %s\n", yytext); }

mov{ARGT}   |
add{ARGT}   |
sub{ARGT}   |
cmp{ARGT}   |
push        |
pop         |
hlt         {   printf("OP %s\n", yytext); }

\%ax        |
\%bx        |
\%cx        |
\%dx        |
\%si        |
\%di        |
\%sp        |
\%bp        {   printf("REG %s\n", yytext); }
\%cs        |
\%ds        |
\%ss        |
\%es        {   printf("SYSREG %s\n", yytext); } 
\%al        |
\%bl        |
\%cl        |
\%dl        |
\%ah        |
\%bh        |
\%ch        |
\%dh        {   printf("REG8 %s\n", yytext); }

,           {   printf("COM\n"); }

"("         {   printf("LPAR\n"); }

")"         {   printf("RPAR\n"); }

\$[ \t]*{ID}    |
\$[ \t]*{DEC}   |
\$[ \t]*{HEX}   {   printf("IMMED %s\n", yytext); }

^[ \t]*{ID}[ \t]*":"  {   printf("LAB %s\n", yytext); }

{ID}        |
{DEC}       |
{HEX}       {   printf("ADDR %s\n", yytext); }

:           {   printf("COL\n"); }

;.*
!.*
#.*

[ \t]+

.           {   printf("scan error %s\n", yytext); }

%%

int main(void)
{
    return yylex();
}

