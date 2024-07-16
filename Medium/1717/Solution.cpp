#include <cstdint>
#include <string>
#include <tuple>
using namespace std;

class Solution {
public:
	int maximumGain(string s, int x, int y) {
		// Initialize variables and determine which patterns ('ab' or 'ba') are going to be the high and low rewards.
		tuple<char, char, uint16_t> highReward = x > y ? make_tuple('a', 'b', x) : make_tuple('b', 'a', y);
		tuple<char, char, uint16_t> lowReward = x > y ? make_tuple('b', 'a', y) : make_tuple('a', 'b', x);

		uint32_t finalScore = 0;
		finalScore += scoreString(s, get<0>(highReward), get<1>(highReward), get<2>(highReward), true); // Score high reward first
		finalScore += scoreString(s, get<0>(lowReward), get<1>(lowReward), get<2>(lowReward), false); // Score low reward with the filtered string.

		return finalScore;
	}
private:
	uint32_t scoreString(string& s, char first, char second, uint16_t reward, bool shouldResize) {
		uint32_t score = 0;
		uint32_t writeIndex = 0; // Index to keep track of the end of the valid substring

		for (char c : s ) {
			if ( writeIndex > 0 && s[writeIndex - 1] == first && c == second ) {
				score += reward;
				writeIndex--; // Remove the matched pattern
			}
			else {
				s[writeIndex++] = c; // Move valid characters to the front
			}
		}

		// Resize the string to the valid part if you're going to score again.
		if (shouldResize) {
			s.resize(writeIndex);
		}

		return score;
	}
};