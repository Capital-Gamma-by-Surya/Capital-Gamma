#ifndef PRIM_OPER_HPP
#define PRIM_OPER_HPP

#include <vector>

namespace calculate {
	int int_sum(int a, int b);

	int int_multiply(int a, int b);

	std::vector<int> int_vec_sum(const std::vector<int>& a, const std::vector<int>& b);
}

#endif