%{
#include <stdio.h>
#include <string.h>
int yylex();
void yyerror(const char *message);
%}
%union {
    double dval;
}
%token <dval> NUMBER 
%type <dval> expr
%type <dval> line

%left FFUN GFUN HFUN
%left LP RP COMMA

%%

line    : expr          { printf("%.3f\n", $1); }
        ;
expr    : FFUN LP expr RP         { 
            // printf("Calculating F Function : x = %.3f", $3);
            $$ = 4*$3 - 1;
        }

        | GFUN LP expr COMMA expr RP         { 
            // printf("Calculating G Function : x = %.3f, y = %.3f", $3, $5);
            $$ = 2*$3 + $5 - 5;
        }

        | HFUN LP expr COMMA expr COMMA expr RP     { 
            // printf("Calculating H Function : x = %.3f, y = %.3f, z = %.3f", $3, $5, $7);
            $$ = 3*$3 - 5*$5 + $7;
        }
        | NUMBER                  {$$ = $1;};

       
%%
void yyerror (const char *message)
{
    printf("Invalid");
    //fprintf (stderr, "%s\n",message);
}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}
int yylex(void);
