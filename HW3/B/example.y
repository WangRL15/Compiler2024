%{
#include <stdio.h>
#include <string.h>
int yylex();
void yyerror(const char *message);
void semanticerror(int col);
extern int col;
%}
%union {
    int ival;
    struct{
        int i;
        int j;
    }matrixval;
}
%type <matrixval> matrix
%token <ival> INUMBER 
%type <matrixval> expr
%left <ival> ADD_MIN
%left <ival> MUL
%right TRANS

%%
line    : expr                  { printf("Accepted"); }
         ;
expr    : expr ADD_MIN expr         {
            if(($1.i == $3.i) && ($1.j == $3.j)){
                $$ = $1;
            }
            else{
                semanticerror($2);
                return(0);
            }
        };
        | expr MUL expr {
            if($1.j == $3.i){
                $$.i = $1.i;
                $$.j = $3.j;
            }
            else{
                semanticerror($2);
                return(0);
            }
        };
        | expr TRANS            {$$.i = $1.j; $$.j = $1.i;};
        | '(' expr ')'            {$$ = $2;};
        | matrix
        ;
matrix  : '[' INUMBER ',' INUMBER ']'       {$$.i = $2; $$.j = $4;}  // set value of matrix
        ;
       
%%
void yyerror (const char *message)
{
        fprintf (stderr, "%s\n",message);
}

void semanticerror (int col)
{
        printf ("Semantic error on col %d\n", col);
}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}
int yylex(void);
