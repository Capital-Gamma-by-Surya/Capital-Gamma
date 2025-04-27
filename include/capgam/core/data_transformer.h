#ifndef DATATRANSFORMER_H
#define DATATRANSFORMER_H

#include <capgam/core/message_structs.h>

class DataTransformer {
   public:
    inline OrderData transform_data(const MarketData& data) const {
        OrderData order;
        order.timestamp = data.timestamp;
        order.mid_price = (data.ask + data.bid) / 2;
        return order;
    }
};

#endif
