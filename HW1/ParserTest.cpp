#include <iostream>
#include <string>
using namespace std;

string input;
string ans = "";
bool judge = true;
int idx = 0;
void stmt();

void error(){
    judge = false;
    cout << "invalid input" << endl;
    exit(0);
}

// check c is an id's first character
bool is_id_head(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

//check c is a part of id
bool is_id(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9');
}

void id(){
    ans += "ID ";
    while(idx < input.length() && is_id(input[idx]))
        ans += input[idx++];
    ans += "\n";
}

bool valid_input(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9') || (c == '(' || c == ')' || c =='.') || (c == ' ' || c == '\n' || c == '"' || c == '$');
}

// primary_tail → DOT ID primary_tail | LBR stmt RBR primary_tail | λ
void primary_tail(){
    if(input[idx] == '.'){
        ans += "DOT .\n";
        idx++;
        if(idx < input.length() && is_id_head(input[idx])){
            id();
            primary_tail();
        }
        else if (input[idx] == '.' && idx >= input.length())
            error();
    }

    else if(input[idx] == '('){
        ans += "LBR (\n";

        if(++idx < input.length())
            stmt();
        
        else{
            error();
            return;
        }

        if(idx < input.length() && input[idx] == ')'){
            ans += "RBR )\n";
            idx++;
            primary_tail();
        }
        else
            error();
    }

    // If λ (empty), do nothing
    else if(valid_input(input[idx])){}

    else
        error();
}

// primary → ID primary_tail
void primary(){
    id();
    primary_tail();
}

// stmt → primary | STRLIT | λ
void stmt(){
    if(input[idx] == '"'){
        ans += "STRLIT \"";
        idx++;
        while(input[idx] != '$' && input[idx] != '"')
            ans += input[idx++];
        
        if(input[idx] != '$' && input[idx] == '"'){
            ans += "\"\n";
            idx++;      //input[idx] == '""
        }
        // unclosed
        else   
            error();
    }

    else if(is_id_head(input[idx]))
        primary();

    // If λ (empty), do nothing
    else if(valid_input(input[idx])){}

    else
        error();
}

// stmts → stmt stmts | λ
void stmts(){
    if(is_id_head(input[idx]) || input[idx] == '"'){
        stmt();
        stmts();
    }
    // skip space
    else if (input[idx] == ' ' || input[idx] == '\n'){
        idx++;
        stmts();
    }
    // If λ (empty), do nothing
    else if(valid_input(input[idx])){}

    else
        error();
}


int main(){
    string s;
    while(getline(cin, s) && !cin.eof())
        input += s;
    input += '$';

    stmts();
    
    if(judge){
        for(char c : ans){
            cout << c;
        }
    }
    else
        cout << "invalid input" << endl;
}