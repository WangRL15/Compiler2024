%{
#include<stdio.h>
int idx;
int i;
int multiComment =  0;
int ifStatement = 0;
%}
%option noyywrap

bookName    ([A-Z][a-z]*[_])*[A-Z][a-z]+
author       [A-Z]+[,][ ][A-Z][a-z]*[-][A-Z][a-z]*
publicationDate      [0-9]{4}[/](02\/(0[1-9]|[12][0-9])|(0[13578]|1[02])[/](0[1-9]|[12][0-9]|30|31)|(0[469]|11)[/](0[1-9]|[12][0-9]|30))
isbn    978-[0-9]-[0-9]{6}-[0-9]{2}-[0-9]
eol \n
other .*
%% 

{bookName} {
    printf("1");
    printf("Book Name: %s\n", yytext);
}

{author} {
    printf("2");
    printf("Author: %s\n", yytext);
}

{publicationDate} {
    printf("3");
    printf("Publication Date: %s\n", yytext);
}

{isbn} {
    printf("4");
    printf("ISBN: %s\n", yytext);
}

\n

{other}

%%
int main(){
    yylex();
    return 0;
}
