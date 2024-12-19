%{
#include "FC.tab.h"
%}
%%
-?[0-9]+(\.[0-9]+)?	{ yylval.dval = atof(yytext);return(NUMBER); }

"f" { return(FFUN); }
"g" { return(GFUN); }
"h" { return(HFUN); }
"("	{ return(LP); }
")"	{ return(RP); }
"," { return(COMMA); }
[ \t]+	{}
\n {return(0);}
.	{ return(yytext[0]); }
%%
int yywrap() {
    return 1;
}