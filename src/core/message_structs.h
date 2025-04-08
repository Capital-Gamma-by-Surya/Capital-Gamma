#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H

#include <cstdint>

struct MarketData {
	std::uint64_t timestamp;
	double bid;
	double ask;
	double last;
};

struct OrderData {
	std::uint64_t timestamp;
	double mid_price;
};

#endif
