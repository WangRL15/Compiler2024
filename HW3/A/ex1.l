%{
#include "ex1.tab.h"
%}
%%
\n	{}
[ \t]+	{}
[0-9]+	{ yylval.ival = atoi(yytext);return(INUMBER); }
"load"	{ yylval.ival = atoi(yytext);return(LOAD); }
"add"	{ yylval.ival = atoi(yytext);return(ADD); }
"sub"	{ yylval.ival = atoi(yytext);return(SUB); }
"mul"	{ yylval.ival = atoi(yytext);return(MUL); }
"mod"	{ yylval.ival = atoi(yytext);return(MOD); }
"inc"	{ yylval.ival = atoi(yytext);return(INC); }
"dec"	{ yylval.ival = atoi(yytext);return(DEC); }
.	{ return(yytext[0]); }
%%
