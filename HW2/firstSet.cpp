#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

map<char, vector<string> > grammar_rule;
map<char, set<char> > firstSet;

set<char> getFirstSet(char s) {
    // If we've already computed first set for this symbol, return it
    if (firstSet.find(s) != firstSet.end()) {
        //cout << s << " : already have first set" << endl;
        return firstSet[s];
    }
    // First(s)
    set<char> first;
    
    // grammar rule of s
    vector<string> g = grammar_rule[s];
    //cout << s << " : start to get its first set." << endl;
    for(string s : g){
        // check if this s rule is already finish finding its first set
        bool finish = false;
        // check each char
        for(int i = 0; i < s.length(); i++){
            // Terminal: insert and break
            if(islower(s[i]) || s[i] == ';' || s[i] == '$'){
                first.insert(s[i]);
                break;
            }
            else{
                // get first set of this nonterminal
                set<char> f = getFirstSet(s[i]);
                // if there's a ';', then erase it and insert the whole set into first set
                // Then continue to check the next char (since there is a ';')
                if((i != s.length()-1) && (f.find(';') != f.end())){
                    //cout << "First set: " << s[i] << " delete lamda " << endl;
                    f.erase(';');
                    first.insert(f.begin(), f.end());
                }
                // if any terminal exists, break and finish finding first set of this rule
                else{
                    for(char j : f){
                        if(islower(j)){
                            first.insert(j);
                            finish = true;
                        }
                        else
                            first.insert(j);
                    }
                }
                if(finish){
                    break;
                }
                
                // for (char c : f) {
                //     cout << c << " ";
                // }
                //cout << endl;
            }
                
            
        }
    }
    //cout << "finish finding first set: " << s << endl;
    firstSet[s] = first;
    return first;
}

int main() {
    map<char, vector<string> >::iterator it;
    char chr;
    string input, tmp;
    // input
    while(true){
        cin >> chr >> input;
        vector<string> t;

        if (input == "ND_OF_GRAMMAR")
            break;
        // split grammar rule by '|'
        grammar_rule.insert(make_pair(chr, t));
        for (int i = 0; i < input.length(); i++){
            if (input[i] != '|')
                tmp += input[i];
            
            else{
                grammar_rule[chr].push_back(tmp);
                tmp = "";
            }
        }	
        grammar_rule[chr].push_back(tmp);
        tmp = "";	   
    }

    // Start finding all first set of every nonterminal by each grammar rule
    for (it = grammar_rule.begin(); it != grammar_rule.end(); ++it) {
        getFirstSet(it->first);
    }

    // print output
    for (it = grammar_rule.begin(); it != grammar_rule.end(); ++it) {
        cout << it->first << " ";
        for (char c : firstSet[it->first]) {
            cout << c;
        }
        cout << endl;
    }
    cout << "END_OF_FIRST" << endl;
    
    return 0;
}