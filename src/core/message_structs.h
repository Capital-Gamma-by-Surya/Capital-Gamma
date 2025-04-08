#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H

#include <cstdint>

struct MarketData {
	std::uint64_t timestamp;
	double bid;
	double ask;
	double last;
	
	MarketData() : timestamp{0}, bid{0}, ask{0}, last{0} {}

	MarketData(std::uint64_t timestamp_, double bid_, double ask_, double last_)
		: timestamp{timestamp_}, bid{bid_}, ask{ask_}, last{last_} {}
};

struct OrderData {
	std::uint64_t timestamp;
	double mid_price;
};

#endif
