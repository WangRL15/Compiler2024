%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // exit(0)
#define MAX_STACK_SIZE 20
int yylex();
int pop();
void dump();
int isEmpty();
void push(int num);
void passing(int num);
void yyerror(const char *message);
int i;
int input_train = 1;
int holding_stack[MAX_STACK_SIZE];

int top = 0;
%}
%union {
    int ival; // 定義數值型別的成員
}
%token END

%type <ival> NUMBERS NUMBER 
%token <ival> INUMBER

%type <ival> expr

%%

line : expr
     ;

expr    : NUMBERS END     { 
            if(!isEmpty())
                yyerror("Error: There is still existing trains in the holding track");
            else
                printf("Success");
        }
        ;
       
NUMBERS : NUMBERS NUMBER {;}
        | NUMBER {;}
        ;

NUMBER : INUMBER { 
    // printf("Dealing with train%d\n", $1);
    passing($1); }
       ;

%%

// return 1 if holding stack is empty
int isEmpty(){
    return(top==0);
}

int pop(){
    return holding_stack[--top];
}

void push(int num){
    printf("Push train %d to holding track\n", num);
    holding_stack[top++] = num;
    dump();
}

void passing(int num){
    if(num == input_train){
        printf("Train %d passing through\n", num);
        input_train++;
        return;
    }
    // the <num> train is in the holding track
    else if(num < input_train){
        // holding stack is empty
        if(isEmpty()){
            yyerror("Error: Impossible to rearrange\nThere is no any train in the holding track");
            exit(0);
        }
        // pop from holding stack
        // printf("holding_stack[top-1]: %d", holding_stack[top-1]);
        // printf("num = %d\n", num);
        if(num == holding_stack[top-1]){
            printf("Moving train %d from holding track\n", num);
            pop();
        }
        // can't pop the right train
        // error
        else{
            printf("Error: Impossible to rearrange\nThe first train in the holding track is train %d instead of train %d", holding_stack[top-1], num);
            exit(0);
        }
    }
    // push <input_train> to the holding track
    else if(top < MAX_STACK_SIZE){
        push(input_train++);
        passing(num);
        // return 0;
    }
    else{
        yyerror("Error: Impossible to rearrange");
    } 
}

// print current holding track
void dump(){
    printf("Current holding track:");
    for(i = 0; i < top; i++){
        printf(" %d", holding_stack[i]);
    }
    printf("\n");
}

void yyerror (const char *message)
{
    printf ("%s\n",message);
}

int main(int argc, char *argv[]) {
    yyparse();
    return(0);
}
int yylex(void);