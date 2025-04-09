#ifndef TIMESERIES_DB_H
#define TIMESERIES_DB_H

#include <atomic>
#include <iostream>

class TimeSeriesDB {
       public:
        TimeSeriesDB(std::size_t capacity) : capacity_{capacity}, index_{0} {
                db_ = new uint64_t[capacity_];
        }

        ~TimeSeriesDB() { delete[] db_; }

        void post(uint64_t data) {
                std::size_t i = index_.fetch_add(1, std::memory_order_relaxed);
                if (i < capacity_) {
                        db_[i] = data;
                } else {
                        std::cerr << "database capacity exceeded..."
                                  << std::endl;
                }
        }

        void print_statistics() {
                std::size_t db_size = index_.load(std::memory_order_relaxed);
                uint64_t min = -1;
                uint64_t max = 0;
                uint64_t total_lat = 0;

                for (std::size_t i = 0; i < db_size; i++) {
                        if (db_[i] < min) {
                                min = db_[i];
                        } else if (db_[i] > max) {
                                max = db_[i];
                        }
                        total_lat += db_[i];
                }

                std::cout << "min. latency: " << min
                          << "ns, max. latency: " << max << "ns" << std::endl;
                std::cout << "avg. latency: " << total_lat / db_size << "ns"
                          << std::endl;
                std::cout << "total latency: " << total_lat / 1000 << "us"
                          << std::endl;
        }

       private:
        const std::size_t capacity_;
        std::atomic<std::size_t> index_;
        uint64_t* db_;
};

#endif
