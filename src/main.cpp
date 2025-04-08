#include <core/message_structs.h>
#include <core/data_transformer.h>
#include <core/order_router.h>

#include <chrono>
#include <vector>

int main() {
	auto get_curr_time = []() { return std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	};

	std::uint64_t stamp = get_curr_time();
	MarketData data{stamp, 15, 30, 18};	

	DataTransformer transformer;
	OrderRouter router;

	OrderData order = transformer.transform_data(data);
	router.route_order(order);

	std::cout << "Total Processing Time: " << get_curr_time() - order.timestamp << "ns" << std::endl;


	return 0;
}
