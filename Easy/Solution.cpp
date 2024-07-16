#include <cstdint>

class Solution {
public: bool isPowerOfTwo(int32_t n) {
	return !(n<=0||n&(n-1)); //  (2^n - 1 = 111...1 (in base two))
	}
};