%{
#include<stdio.h>
int idx;
int i;
int multiComment =  0;
int ifStatement = 0;
%}
%option noyywrap

MultiCommentLeft    [\t]*[/][\*]
MultiCommentRight   [\t]*[\*][/]
SingleComment       ^[\t]*[/][/][^\n]*
PrintStatement      ^[\t]*cout.*
iff                 ^[\t]*if.*
endif               ^[\t]*\}[\n]?
other               .*
eol                 \n
%%
{MultiCommentLeft}  {
    for(idx = 0; idx < yyleng; idx++){
        if(yytext[idx] != '\t')
            break;
        printf("%c", yytext[idx]);
    }
    multiComment = 1;
    printf("\"\"\"");
}

{MultiCommentRight}  {
    for(idx = 0; idx < yyleng; idx++){
        if(yytext[idx] != '\t')
            break;
        printf("%c", yytext[idx]);
    }
    printf("\"\"\"");
}

{SingleComment}  {
    for( i = 0; i < yyleng; i++){
        if(yytext[i] != '\t')
            break;
        printf("%c", yytext[i]);
    }
    printf("#%s", yytext + i + 2);
}

{PrintStatement} {
    if(inComment){
        ECHO;
    }

    else{
        for(idx = 0; idx < yyleng; idx++){
            if(yytext[idx] != '\t')
                break;
            printf("%c", yytext[idx]);
        }
        printf("print(");
        idx += 8;

        for(; idx < yyleng; idx++){
            if(yytext[idx] == ' ')
                break;
            printf("%c", yytext[idx]);
        }
        printf(")");
    }
}

{iff} {
    for(idx = 0; idx < yyleng; idx++){
        if(yytext[idx] != '\t')
            break;
        printf("%c", yytext[idx]);
    }
    ifStatement = 1;
    idx += 3;

    if(yytext[idx] == 't'){
        printf("if True:");
    }

    else if(yytext[idx] == 'f'){
        printf("if False:");
    }
}

{endif} {
    ifStatement = 0;
}

{other} {
    for(int i = 0; i < yyleng; i++){
        printf("%c", yytext[i]);
    }
}

{eol} {
    printf("\n");
}

%%
int main(){
    yylex();
    return 0;
}
