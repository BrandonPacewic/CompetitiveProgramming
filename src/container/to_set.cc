#include <set>
#include <unordered_set>

template<typename T_container>
std::set<char> to_set(const T_container& container) {
	std::set<char> set_obj(container.begin(), container.end());
	return set_obj;
}

template<typename T_container>
std::unordered_set<char> to_unordered_set(const T_container& container) {
	std::unordered_set<char> set_obj(container.begin(), container.end());
	return set_obj;
}