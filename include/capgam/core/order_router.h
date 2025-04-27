#ifndef ORDERROUTER_H
#define ORDERROUTER_H

#include <capgam/core/message_structs.h>

#include <iostream>

class OrderRouter {
   public:
    inline void route_order(const OrderData& order) const {
        // std::cout << "Routing order: time = " << order.timestamp
        //	<< ", mid price=" << order.mid_price << std::endl;
    }
};

#endif
