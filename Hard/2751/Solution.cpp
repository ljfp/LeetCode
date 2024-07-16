#include <numeric>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
	vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
		int n = positions.size();
		vector<int> indices(n);

		// Initialize indices with 0, 1, ..., n-1 (remember robots are 1-indexed) and sort indices based on the positions of the robots.
		iota(indices.begin(), indices.end(), 0);
		sort(indices.begin(), indices.end(), [&positions](int i, int j) { return positions[i] < positions[j]; });

		// Iterate through the sorted indices and process the robots handling collisions in the process.
		vector<int> result(n, 0); // Vector to store the final health of robots.
		vector<int> st; // Stack to keep track of indices of robots moving to the right.
		st.reserve(n); 
		for (int i : indices) {
			if (directions[i] == 'R') { st.emplace_back(i); } 
			else {
				while (!st.empty()) {
					int j = st.back();
					if (healths[j] > healths[i]) {
						healths[j] -= 1;
						healths[i] = 0;
						break;
					} else if (healths[j] < healths[i]) {
						st.pop_back();
						healths[i] -= 1;
					} else {
						st.pop_back();
						healths[i] = 0;
						break;
					}
				}
				if (healths[i] > 0) { result[i] = healths[i]; }
			}
		}

		// Add to the vector holding the collisions results the remaining robots moving to the right.
		for (int i : st) { result[i] = healths[i]; }

		// Add the health of the surviving robots to the vector we'll return.
		vector<int> survivors;
		survivors.reserve(n);
		for (int health : result) { if (health > 0) { survivors.push_back(health); } }
		return survivors;
	}
};