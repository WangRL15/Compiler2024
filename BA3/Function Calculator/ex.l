%{
#include "ex.tab.h"
%}
%%

[1-9][0-9]*	{ yylval.ival = atoi(yytext);return(INUMBER); }
0 { return(END); }
.	{;}
%%
int yywrap() {
    return 1;
}