#include <capgam/math/primative_operators.hpp>

namespace calculate {
	int int_sum(int a, int b) {
		return a + b;
	}

	int int_multiply(int a, int b) {
		return a * b;
	}

	std::vector<int> int_vec_sum(std::vector<int> a, std::vector<int> b) { 
		std::vector<int> result;
		int n_elems = b.size(); 
		for (int i = 0; i < n_elems; i++) {
			result.push_back(a[i] + b[i]);
		}

		return result;
	}
}