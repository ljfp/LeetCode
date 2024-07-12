#include <cstdint>
#include <string>
#include <tuple>

class Solution {
public:
    int maximumGain(string s, int x, int y) {
        // Initialize variables and determine which patterns ('ab' or 'ba') are going to be the high and low rewards.
        uint32_t finalScore = 0;
        tuple<char, char, uint16_t> highReward, lowReward;
        if ( x > y )
        {
            highReward = make_tuple('a', 'b', x);
            lowReward = make_tuple('b', 'a', y);
        }
        else
        {
            highReward = make_tuple('b', 'a', y);
            lowReward = make_tuple('a', 'b', x);
        }

        auto scoreString = [](string &s, char first, char second, uint16_t reward, bool shouldResize) -> uint32_t {
            uint32_t score = 0;
            uint32_t i = 0;  // Index to keep track of the end of the valid substring

            for (char c : s)
            {
                if (i > 0 && s[i - 1] == first && c == second)
                {
                    score += reward;
                    i--;  // Remove the matched pattern
                } 
                else
                {
                    s[i++] = c;  // Move valid characters to the front
                }
            }

            // Resize the string to the valid part if you're going to score again.
            if (shouldResize)
            {
                s.resize(i);
            }
            return score;
        };

        // Score high reward first
        finalScore += scoreString(s, get<0>(highReward), get<1>(highReward), get<2>(highReward), true);

        // Score low reward with the filtered string.
        finalScore += scoreString(s, get<0>(lowReward), get<1>(lowReward), get<2>(lowReward), false);

        return finalScore;
    }
};