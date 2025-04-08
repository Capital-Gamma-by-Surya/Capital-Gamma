#ifndef DATA_TRANSFORMER_H
#define DATA_TRANSFORMER_H

#include <core/message_structs.h>
#include <common/scoped_timer.h>

class DataTransformer {
public:
	inline OrderData transform_data(const MarketData& data) const {
		ScopedTimer timer{"transform_data"};
		OrderData order;
		order.timestamp = data.timestamp;
		order.mid_price = (data.ask + data.bid)/2;
		return order;
	}
};

#endif
