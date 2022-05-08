// * [1,1,1] -> 1, because after you pick on day one, there will be only one chip left
// * [1,2,1] -> 2, you can pick twice; you pick two chips on day one then on day two
// * [4,1,1] -> 2

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

int solve(std::vector<int> v) {
	assert(int(v.size()) == 3);

	std::sort(v.begin(), v.end());
	
	return std::min(std::accumulate(v.begin(), v.end(), 0) / 2 | 0, v[0] + v[1]);
}