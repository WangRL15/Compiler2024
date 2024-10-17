#include <iostream>
#include <string>
using namespace std;

string input;
string ans = "";
bool judge = true;
int idx = 0;
void stmt();

bool is_shceme(){
    int i = 0;
    //https
    if((i+4) < input.length()-1 && input.substr(i, i + 5) == "https")
        return true;

    // tel
    else if((i+2) < input.length()-1 && input.substr(i, i + 3) == "tel"){
       return true;
    }
    //mailto
    else if((i+5) < input.length()-1 && input.substr(i, i + 6) == "mailto"){
        return true;
    }
    return false;
}

void error(){
    judge = false;
    cout << "Invalid input" << endl;
    exit(0);
}

void path(){
    if(idx >= input.length()-1 || !(isalpha(input[idx]) || isdigit(input[idx])))
        error();
        
    while(idx < input.length()-1 && (isalpha(input[idx]) || isdigit(input[idx])))
        ans += input[idx++];
    ans += " PATH\n";
}

void domain(){
    if((idx + 2) >= input.length()-1 || (input.substr(idx,3) != "com" && input.substr(idx,3) != "org"))
        error();
    ans += input.substr(idx, 3);
    ans += " DOMAIN\n";
    idx += 3;
    // end
    if(input[idx] != '$')
        error();
}

void dot(){
    if(idx >= input.length()-1 || input[idx++] != '.')
        error();
    ans += ". DOT\n";
}

void phonenum(){
    if(input.length()-1 != 11)
        error();

    for(int i = 2; i < 10; i++){
        if(!isdigit(input[i]))
            error();
    }
    ans += input;
    ans += " PHONENUM\n";
}

// mail -> PATH AT MAILDOMAIN DOT DOMAIN
void mail(){
    // PATH
    path();

    // AT
    if(idx >= input.length()-1 || input[idx++] != '@')
        error();
    ans += '@';
    ans += " AT\n";

    // MAILDOMAIN
    //(gmail|yahoo|iCloud|outlook)
    if((idx+4) < input.length()-1 && input.substr(idx, 5) == "gmail"){
        ans +="gmail";
        idx += 5;
    }
    else if((idx+4) < input.length()-1 &&input.substr(idx, 5) == "yahoo"){
        ans +="yahoo";
        idx += 5;
    }
    else if((idx+5) < input.length()-1 &&input.substr(idx, 6) == "iCloud"){
        ans +="iCloud";
        idx += 6;
    }
    else if((idx+6) < input.length()-1 &&input.substr(idx, 7) == "outlook"){
        ans +="outlook";
        idx += 7;
    }
    else
        error();

    ans += " MAILDOMAIN\n";

    // DOT
    dot();

    // DOMAIN
    domain();
}

// URL -> SCHEME COLON SLASH SLASH PATH DOT DOMAIN || SCHEME COLON mail || SCHEME COLON PHONENUM
void uri(){
    // SCHEME

    //https
    if((idx+4) < input.length()-1 && input.substr(idx, idx + 5) == "https"){
        ans +="https";
        idx += 5;
    }

    // tel
    else if((idx+2) < input.length()-1 && input.substr(idx, idx + 3) == "tel"){
        ans +="tel";
        idx += 3;
    }

    //mailto
    else if((idx+5) < input.length()-1 && input.substr(idx, idx + 6) == "mailto"){
        ans +="mailto";
        idx += 6;
    }

    else
        error();

    ans += " SCHEME\n";

    // COLON
    if(idx >= input.length()-1 || input[idx++] != ':')
        error();
    ans += ':';
    ans += " COLON\n";


    // //
    if((idx+1) < input.length()-1 && input.substr(idx, 2) == "//"){
        ans +="/ SLASH\n/ SLASH\n";
        idx += 2;
        path();
        dot();
        domain();
    }

    // mail
    else if(isalpha(input[idx]) || isdigit(input[idx]))
        mail();

    // phonenum
    else if(input[0] == '0' && input[1] == '9')
        phonenum();

    else
        error();
}

// stmt → PHONENUM | MAIL | URI
void stmt(){
    // PHONENUM
    if(input[0] == '0' && input[1] == '9')
        phonenum();
    // URI
    else if(is_shceme())
        uri();
    // MAIL
    else if (isalpha(input[0]) || isdigit(input[0]))
        mail();

}

// program → stmt program | λ
void program(){
    stmt();
}


int main(){
    string s;
    cin >> input;
    input += "$";

    program();
    
    if(judge){
        for(char c : ans){
            cout << c;
        }
    }

}

