#include <core/message_structs.h>
#include <core/data_transformer.h>
#include <core/order_router.h>
#include <core/ring_buffer.h>
#include <common/scoped_timer.h>

#include <chrono>
#include <thread>
#include <vector>

constexpr int NUM_TICKS = 5000;
constexpr std::size_t RING_BUFFER_SIZE = 64;

std::uint64_t get_curr_time() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void vector_buffer() {
	std::vector<MarketData> market_inputs;
	market_inputs.reserve(NUM_TICKS);

	DataTransformer transformer;
	OrderRouter router;

	std::uint64_t total_latency = 0;

	std::uint64_t start_time = get_curr_time();
	for ( size_t i = 0; i<NUM_TICKS; i++ ) {
		std::uint64_t stamp = get_curr_time();
		market_inputs.emplace_back(stamp, 15.0, 30.0, 18.0);	
	}

	for ( const auto& market_input : market_inputs) {
		total_latency += (get_curr_time() - market_input.timestamp);
		OrderData order = transformer.transform_data(market_input);
		router.route_order(order);
	}

	std::cout << "Total Processing Time Vector: " << (get_curr_time() - start_time)/1000 << "us" << std::endl;
	std::cout << "vector total latency: " << total_latency/1000 << "us" << std::endl;
	std::cout << "vector average latency: " << (total_latency)/NUM_TICKS << "ns" << std::endl;
}


void producer(RingBuffer<MarketData, RING_BUFFER_SIZE>& ring_buff) {
	ScopedTimer producer_timer{"producer"};
	for (int i = 0; i<NUM_TICKS; i++) {
		MarketData market_input{get_curr_time(), 15.0, 30.0, 18.0};
		while(!ring_buff.push(market_input)) {
			std::this_thread::yield();
		}
	}
}

void consumer(RingBuffer<MarketData, RING_BUFFER_SIZE>& ring_buff, DataTransformer& transformer, OrderRouter& router) {
	ScopedTimer consumer_timer{"consumer"};
	MarketData market_data;
	std::size_t count = 0;
	std::uint64_t total_latency = 0;
	while(true) {
		if(ring_buff.pop(market_data)) {
			count++;
			OrderData transformed_data = transformer.transform_data(market_data);
			router.route_order(transformed_data);
			total_latency += (get_curr_time() - market_data.timestamp);
		} else {
			std::this_thread::yield();
		}
		if(count==NUM_TICKS) {
			std::cout << "ring total latency: " << total_latency/1000 << "us" << std::endl;
			std::cout << "ring average latency: " << (total_latency)/NUM_TICKS << "ns" << std::endl;
			break;
		}
	}
}

void ring_buffer() {
	RingBuffer<MarketData, RING_BUFFER_SIZE> ring;

	DataTransformer transformer;
	OrderRouter router;

	std::uint64_t start_time = get_curr_time();

	std::thread producer_thread{producer, std::ref(ring)};
	std::thread consumer_thread{consumer, std::ref(ring), std::ref(transformer), std::ref(router)};

	producer_thread.join();
	consumer_thread.join();

	std::cout << "Total Processing Time Ring: " << (get_curr_time() - start_time)/1000 << "micros" << std::endl;
}

int main() {
	ring_buffer();

	vector_buffer();

	return 0;
}
