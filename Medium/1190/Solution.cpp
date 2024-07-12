#include <string>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    string reverseParentheses(string s) {
        stack<uint16_t, vector<uint16_t>> lifo;
        uint16_t cleanupIndex = 0;
        
        for (uint16_t i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                lifo.push(cleanupIndex); // Push the index where '(' would have been written.
            } else if (s[i] == ')') {
                uint16_t j = lifo.top();
                lifo.pop();

                // We only reverse the substring if there's more than 1 character.
                if (cleanupIndex - j > 1) {
                    reverse(s.begin() + j, s.begin() + cleanupIndex);
                }
            } else {
                s[cleanupIndex++] = s[i]; // We only want to write non-parenthesis characters.
            }
        }
        
        s.resize(cleanupIndex); // Resize the string to remove the leftover characters.
        
        return s;
    }
};