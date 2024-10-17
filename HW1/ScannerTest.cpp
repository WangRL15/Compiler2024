#include <iostream>
#include <string>
using namespace std;

// ALL THE TOKEN TYPE (INCLUDE THE_END TO EXPRESS THE END OF THE INPUT)
enum token_type{
    PHONENUM,
    PATH,
    MAILDOMAIN,
    DOMAIN,
    COLON,
    AT,
    DOT,
    SLASH,
    THE_END
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

        // GET THE WHOLE NUMBER AND THEN RETURN ITS TOKEN
        Token num(){
                string number;
                number += input[--position];
                position++;
                while(isdigit(input[position]))
                    number += input[position++];
                return {number, NUM};
            }


    public:
        Scanner(const string& input): input(input), position(0){}
        Token get_next_token(){
            skip_space();

            // end of input
            if(position >= input.length())
                return {"\n", THE_END};

            curr = input[position++];

            switch (curr)
            {
            case '+':
                return {"+", PLUS};
            case '-':
                return {"-", MINUS};
            case '*':
                return {"*", MUL};
            case '/':
                return {"/", DIV};
            case '(':
                return {"(", LPR};

            case ')':
                return {")", RPR};
            
            default:
                if(isdigit(curr))
                    return num();
                
                return {"\n", THE_END};
            }
            
        }

};

// CHANGE TOKEN TYPE TO STRING AND THEN PRINT 
void print_token_type(Token token){
    switch (token.type)
    {
    case NUM:
        cout << "NUM";
        return;
    case PLUS:
        cout << "PLUS";
        return;
        case MINUS:
        cout << "MINUS";
        return;
    case DIV:
        cout << "DIV";
        return;
    case MUL:
        cout << "MUL";
        return;
    case LPR:
        cout << "LPR";
        return;
    case RPR:
        cout << "RPR";
        return;   
    default:
        break;
    }
}

int main(){
    // INPUT
    string input;
    string s;

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
                cout << endl;
            else 
                first_token = false;
            
            print_token_type(token);

            if(token.type == NUM)
                cout << " " << token.value;
            

    } while(true);
}

