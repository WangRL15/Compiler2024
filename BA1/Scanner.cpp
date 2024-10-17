#include <iostream>
#include <string>
using namespace std;


// ALL THE TOKEN TYPE (INCLUDE THE_END TO EXPRESS THE END OF THE INPUT)
enum token_type{
    NUM,
    IDENTIFIER,
    SYMBOL,
    KEYWORD,
    THE_END,
    ERROR
};

struct Token{
    string value;
    token_type type;
};

class Scanner{
        private:
        string input;
        int position;
        char curr;

        void error(){
            cout << "invalid input" << endl;
            exit(0);
        }
        // SKIP ALL THE SPACE
        void skip_space(){
            while(position < input.length() && isspace(input[position]))
                position++;
        }

        // GET THE WHOLE NUMBER AND THEN RETURN ITS TOKEN
        Token num(){
            string number;
            number += input[--position];

            if(isdigit(input[++position]) && number == "0" )
                return {number, NUM};
                
            while(isdigit(input[position]))
                number += input[position++];
            return {number, NUM};
        }

        Token identifier(){
            string id;
            id += input[--position];
            position++;
            while(isalpha(input[position]) || isdigit(input[position]))
                id += input[position++];
            return {id, IDENTIFIER};
        }

        bool is_keyword(){
            if(input.substr(position-1, 2) == "if")
                return true;
            if(input.substr(position-1, 5) == "while")
                return true;
            else
                return false;
        }

    public:
        Scanner(const string& input): input(input), position(0){}
        Token get_next_token(){
            skip_space();

            // end of input
            if(position >= input.length())
                return {"\n", THE_END};

            curr = input[position++];

            if(is_keyword()){
                position--;
                if(input.substr(position, 2) == "if"){
                    position += 2;
                    return {"if", KEYWORD};
                }
                if(input.substr(position, 5) == "while"){
                    position += 5;
                    return {"while", KEYWORD};
                }
            }
            if(isdigit(curr))
                return num();

            if(isalpha(curr))
                return identifier();

            switch (curr)
            {
            case '+':
                return {"+", SYMBOL};
            case '-':
                return {"-", SYMBOL};
            case '*':
                return {"*", SYMBOL};
            case '/':
                return {"/", SYMBOL};
            case '=':
                return {"=", SYMBOL};
            case '(':
                return {"(", SYMBOL};
            case ')':
                return {")", SYMBOL};
            case '{':
                return {"{", SYMBOL};
            case '}':
                return {"}", SYMBOL};
            case '>':
                return {">", SYMBOL};
            case '<':
                return {"<", SYMBOL};
            case ';':
                return {";", SYMBOL};
            
            default:
                return {"", ERROR};
            }
            
        }

};

// CHANGE TOKEN TYPE TO STRING AND THEN PRINT 
string get_token_type(Token token){
    switch (token.type)
    {
    case NUM:
        return "NUM";
    case SYMBOL:
        return "SYMBOL";
    case IDENTIFIER:
        return "IDENTIFIER";
    case KEYWORD:
        return "KEYWORD";
    default:
        break;
    }
}

int main(){
    // INPUT
    string input = "";
    string s;
    string ans = "";

    while(getline(cin, s) && !cin.eof())
        input += s;
    Scanner scanner(input);

    // START SCANNING
    bool first_token = true;
    do{
            Token token = scanner.get_next_token();

            // End of the input
            if(token.type == THE_END && token.value == "\n")
                break;

            if (!first_token) 
                ans += "\n";
            else 
                first_token = false;

            if(token.type == ERROR){
                ans += "Invalid";
                continue;
            }
            
            ans += get_token_type(token);

            ans += " \"";
            ans += token.value;
            ans += "\"";

    } while(true);

    cout << ans;
}