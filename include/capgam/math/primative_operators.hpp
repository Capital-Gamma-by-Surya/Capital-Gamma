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

	template <typename T>
	std::vector<T> vec_sum(const std::vector<T>& a, const std::vector<T>& b) { 
		size_t n_elems = b.size(); 
		std::vector<T> result;
		result.reserve(n_elems);

		for (size_t i = 0; i < n_elems; i++) {
			result.push_back(a[i] + b[i]);
		}

		return result;
	}
}

#endif