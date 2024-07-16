#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <cctype>
#include <stack>

using namespace std;

class Solution {
public:
	string countOfAtoms(string formula) {
		uint32_t readIndex = 0;
		unordered_map<string, uint32_t> atomCounts;
		stack<unordered_map<string, uint32_t>> lifo;
		uint16_t n = formula.size();

		while (readIndex < n) {
			if (formula[readIndex] == '(') {
				lifo.push(move(atomCounts));
				atomCounts.clear();
				++readIndex;
			} else if (formula[readIndex] == ')') {
				++readIndex;
				int multiplier = parseNumber(formula, readIndex);
				if (multiplier == 1 && readIndex < n && isdigit(formula[readIndex])) {
					multiplier = parseNumber(formula, readIndex);
				}
				unordered_map<string, uint32_t> top = move(atomCounts);
				atomCounts = move(lifo.top());
				lifo.pop();
				for (const auto& [atom, count] : top) {
					atomCounts[atom] += count * multiplier;
				}
			} else {
				string atom = parseAtom(formula, readIndex);
				int count = parseNumber(formula, readIndex);
				atomCounts[atom] += count;
			}
		}

		map<string, uint32_t> sortedCounts(atomCounts.begin(), atomCounts.end());
		string result;
		for (const auto& [atom, count] : sortedCounts) {
			result += atom;
			if (count > 1) {
				result += to_string(count);
			}
		}

		return result;
	}

private:
	// TODO: Refactor using isalpha(), isdigit(), islower(), and isupper() instead of check().
	enum CharacterType {
		UPPERCASE,
		LOWERCASE,
		DIGIT,
		PARENTHESES,
		OTHER
	};

	inline CharacterType check(char c) const {
		if (c >= 'A' && c <= 'Z')
			return UPPERCASE;
		else if (c >= 'a' && c <= 'z')
			return LOWERCASE;
		else if (c >= '0' && c <= '9')
			return DIGIT;
		else if (c == '(' || c == ')')
			return PARENTHESES;
		else
			return OTHER;
	}

	inline string parseAtom(const string& formula, uint32_t& index) {
		string atom;
		atom += formula[index++];
		while (index < formula.size() && islower(formula[index])) {
			atom += formula[index++];
		}
		return atom;
	}

	inline int parseNumber(const string& formula, uint32_t& index) {
		if (index >= formula.size() || !isdigit(formula[index])) {
			return 1;
		}
		int number = 0;
		while (index < formula.size() && isdigit(formula[index])) {
			number = number * 10 + (formula[index++] - '0');
		}
		return number;
	}
};