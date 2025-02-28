#include <capgam/math/primative_operators.hpp>

namespace calculate {
	int int_sum(int a, int b) {
		return a + b;
	}

	int int_multiply(int a, int b) {
		return a * b;
	}

	std::vector<int> int_vec_sum(const std::vector<int>& a, const std::vector<int>& b) { 
		int n_elems = b.size(); 
		std::vector<int> result(n_elems);
		for (int i = 0; i < n_elems; i++) {
			result[i] = a[i] + b[i];
		}

		return result;
	}
}