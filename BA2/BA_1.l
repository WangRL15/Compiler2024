 %{
#include<stdio.h>
int idx;
int i;
int multiComment =  0;
int isFirst = 1;
%}
%option noyywrap

INTERGER    [0-9]+
FLOAT       ([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)
STRING      (\"[^\"\n]*\"|\'[^\'\n]*\')
BOOLEAN     "true"|"false"
OPERATION   ([0-9]+([+]|[-]|[*]|[/])+[0-9]*)*
other       [^\n]*

%% 

{INTERGER} {

    printf("%s INTEGER", yytext);
}

{FLOAT} {

    printf("%s FLOAT", yytext);
}

{STRING} {

    printf("%s STRING", yytext);
}

{BOOLEAN} {

    printf("%s BOOLEAN", yytext);
}

{OPERATION} {

    printf("%s OPERATION", yytext);
}

{other} {

    printf("%s INVALID", yytext);
}

%%
int main(){
    yylex();
    return 0;
}
