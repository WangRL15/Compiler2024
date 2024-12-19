%{
#include <stdio.h>
#include <string.h>
int yylex();
void yyerror(const char *message);
int judge = 1;
int ans;
%}
%union {
    int ival; // 定義數值型別的成員
}
%token LOAD
%token ADD
%token SUB
%token MUL
%token MOD
%token INC
%token DEC
%token <ival> INUMBER
%type <ival> expr
%type line

%%
line    : expr              { ans = $1; }
        ;
expr    : expr expr ADD     {$$ = $2 + $1;}
        | expr expr SUB     {$$ = $2 - $1;}
        | expr expr MUL     {$$ = $2 * $1;}
        | expr expr MOD     {$$ = $2 % $1;}
        | expr INC          {$$ = $1 + 1;}
        | expr DEC          {$$ = $1 - 1;}
        | LOAD INUMBER      {$$ = $2;}
        ;
       
%%
void yyerror (const char *message)
{
    judge = 0;
    fprintf (stderr, "%s\n",message);
}

int main(int argc, char *argv[]) {
        yyparse();
        if(judge){
            printf("%d", ans);
        }
        else
            printf("Invalid format");
        return(0);
}
int yylex(void);