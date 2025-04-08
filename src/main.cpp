#include <core/message_structs.h>
#include <core/data_transformer.h>
#include <core/order_router.h>
#include <core/ring_buffer.h>

#include <chrono>
#include <thread>
#include <vector>

constexpr int NUM_TICKS = 5000;
constexpr std::size_t RING_BUFFER_SIZE = 256;

std::uint64_t get_curr_time() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void vector_buffer() {
	std::uint64_t start_time = get_curr_time();

	std::vector<MarketData> market_inputs;
	market_inputs.reserve(NUM_TICKS);

	for ( size_t i = 0; i<NUM_TICKS; i++ ) {
		std::uint64_t stamp = get_curr_time();
		market_inputs.emplace_back(stamp, 15.0, 30.0, 18.0);	
	}

	DataTransformer transformer;
	OrderRouter router;

	for ( const auto& market_input : market_inputs) {
		std::cout << "latency: " << (get_curr_time() - market_input.timestamp)/1000 << " micros" << std::endl;
		OrderData order = transformer.transform_data(market_input);
		router.route_order(order);
	}
}


void producer(RingBuffer<MarketData, RING_BUFFER_SIZE>& ring_buff) {
	for (int i = 0; i<NUM_TICKS; i++) {
		MarketData market_input{get_curr_time(), 15.0, 30.0, 18.0};
		while(!ring_buff.push(market_input)) {
			std::this_thread::yield();
		}
	}
}

void consumer(RingBuffer<MarketData, RING_BUFFER_SIZE>& ring_buff, DataTransformer& transformer, OrderRouter& router) {
	MarketData market_data;
	while(true) {
		if(ring_buff.pop(market_data)) {
			OrderData transformed_data = transformer.transform_data(market_data);
			router.route_order(transformed_data);
			std::cout << "latency: " << (get_curr_time() - market_data.timestamp)/1000 << "micros" << std::endl;
		} else {
			std::this_thread::yield();
		}
		if(market_data.timestamp > 0 && market_data.timestamp % 10000 == 0) {
			break;
		}
	}
}

void ring_buffer() {
	std::uint64_t start_time = get_curr_time();

	RingBuffer<MarketData, RING_BUFFER_SIZE> ring;

	DataTransformer transformer;
	OrderRouter router;

	std::thread producer_thread{producer, std::ref(ring)};
	std::thread consumer_thread{consumer, std::ref(ring), std::ref(transformer), std::ref(router)};

	producer_thread.join();
	consumer_thread.join();

	std::cout << "Total Processing Time: " << (get_curr_time() - start_time)/1000 << "micros" << std::endl;
}

int main() {
	std::uint64_t start_time = get_curr_time();

	ring_buffer();


	std::cout << "Total Processing Time: " << (get_curr_time() - start_time)/1000 << "micros" << std::endl;

	return 0;
}
