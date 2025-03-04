#ifndef PRIM_OPER_HPP
#define PRIM_OPER_HPP

#include <vector>

namespace calculate {
	template <typename T>
	T sum(T a, T b) {
		return a + b;
	}

	template <typename T>
	T multiply(T a, T b) {
		return a * b;
	}

	std::vector<int> int_vec_sum(const std::vector<int>& a, const std::vector<int>& b);
}

#endif