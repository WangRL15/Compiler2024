%{
#include<stdio.h>
int tab_count=0;
int i;
%}
%option noyywrap

Left    ^.*\{.*$
Right   ^.*\}.*$
QQ     ^\t*.*$
%%
{Left}  {
    for(i = 0; i < tab_count; i++)
        printf("\t");

    for(i = 0; i < yyleng; i++){
         if(yytext[i] != '\t')
               break;
    }

    //continue to print other text
    for(; i < yyleng; i++)
        printf("%c",yytext[i]);
    
    printf("\n");

    tab_count++;
}

{Right} {
    tab_count--;

    for(i = 0; i < tab_count; i++)
        printf("\t");

    for(i = 0; i < yyleng; i++)
    {
         if(yytext[i] != '\t')
               break;
   }

    for(; i < yyleng ; i++)
        printf("%c",yytext[i]);
    
    printf("\n");
}
\n  {
    // do nothing       
}
{QQ} {
    for(i = 0; i < tab_count; i++)
        printf("\t");
    for(i = 0; i < yyleng; i++)
        if(yytext[i]!='\t')
            break;
    for(; i < yyleng; i++){
        printf("%c",yytext[i]);
    }
    printf("\n");
}
%%
int main(){
    yylex();
    return 0;
}
