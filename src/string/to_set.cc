#include <set>
#include <string>

std::set<char> to_set(std::string str) {
	std::set<char> set_obj(str.begin(), str.end());
	return set_obj;
}