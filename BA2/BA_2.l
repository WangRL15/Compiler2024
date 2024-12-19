%{
#include <stdio.h>
int tabcount = 0;
int count;
int inComment = 0;
int i;
void checkScope(){
    count = 0;
    for(i = 0; i < yyleng; i++){
        if(yytext[i] != '\t')
            break;
        count++;
    }
    while(count < tabcount){
        tabcount--;
        for(i = 0; i < tabcount; i++){
            printf("\t");
        }
        printf("}\n");
    }
    for(i = 0; i < count; i++){
        printf("\t");
    }
}
%}

single      [\t]*"# ".*
multiple    [\t]*["]{3}
print       [\t]*"print(".+")"
iftrue      [\t]*"if True:"
iffalse     [\t]*"if False:"
other       .*
eol          \n

%%

{single} {
    checkScope();
    printf("// %.*s", (int)yyleng-2-i, yytext + 2 + i);

}

{multiple} {
    checkScope();
    if(inComment){
        printf("*/");
        inComment--;
    }
    else{
        printf("/*");
        inComment++;
    }
}

{print} {
    if(inComment){
        ECHO;
    }

    else{
        checkScope();
        printf("cout << ");
        printf("%.*s", (int)yyleng-7-i, yytext + 6 + i);
        printf(" << endl;");
    }
}

{iftrue} {
    if(inComment){
        ECHO;
    }
    else{
        checkScope();
        tabcount++;
        printf("if(true) {");
    }
}

{iffalse} {
    if(inComment){
        ECHO;
    }
    else{
        checkScope();
        tabcount++;
        printf("if(false) {");
    }
}

{eol} {
    printf("\n");
}

{other} {
    ECHO;
}

%%

int main() {
    yylex();
    checkScope();
    return 0;
}

int yywrap() {
    return 1;
}
