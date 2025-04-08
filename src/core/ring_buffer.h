#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <atomic>
#include <array>

constexpr std::size_t CACHE_LINE_SIZE = 64;

template <typename T, std::size_t buffer_size>
class RingBuffer {
	static_assert((buffer_size & (buffer_size-1)) == 0, "Buffer size must be power of 2");
public:
	RingBuffer() : head_{0}, tail_{0} {}

	bool push(T& data) {
		std::size_t head = head_.load(std::memory_order_relaxed);
		std::size_t next_head = (head + 1) & (buffer_size - 1);
		if (next_head == tail_.load(std::memory_order_acquire)) {
			return false;
		}
		buffer_[head] = data;
		head_.store(next_head, std::memory_order_release);
		return true;
	}

	bool pop(T& data) {
		std::size_t tail = tail_.load(std::memory_order_relaxed);
		if (tail == head_.load(std::memory_order_acquire)) {
			return false;
		}
		data = buffer_[tail];
		tail_.store((tail+1) & (buffer_size-1), std::memory_order_release);
		return true;
	}

	bool empty() {
		return tail_.load(std::memory_order_acquire) == head_.load(std::memory_order_acquire);
	}

	bool full() {
		std::size_t next_head = (head_.load(std::memory_order_relaxed) + 1) & (buffer_size - 1);
		return next_head == tail_.load(std::memory_order_acquire);
	}

private:
	alignas(CACHE_LINE_SIZE) std::atomic<std::size_t> head_;
	alignas(CACHE_LINE_SIZE) std::atomic<std::size_t> tail_;
	alignas(CACHE_LINE_SIZE) std::array<T, buffer_size> buffer_;
};

#endif
