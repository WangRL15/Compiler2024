%{
#include "example.tab.h"
int col;
%}
%%
\n	{ return(0); /* EOF */ }
[ \t]+	{ col += yyleng; }
[0-9]+	{ col += yyleng; yylval.ival = atoi(yytext);return(INUMBER); }
"+"|"-"	{ col += yyleng; yylval.ival = col;return(ADD_MIN); }
"*"	{ col += yyleng; yylval.ival = col;return(MUL); }
"^T"	{ col += yyleng; return(TRANS); }
"("|")"|"["|"]"|","	{ col += yyleng; return(yytext[0]); }
.	{ return(yytext[0]); }
%%
