#ifndef SCOPED_TIMER_H
#define SCOPED_TIMER_H

#include <chrono>
#include <iostream>

class ScopedTimer {
       public:
        ScopedTimer(const char* label)
            : label_{label},
              start_{std::chrono::high_resolution_clock::now()} {}

        ~ScopedTimer() {
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed =
                    std::chrono::duration_cast<std::chrono::microseconds>(
                        end - start_);
                std::cout << label_ << " took " << elapsed.count() << "us"
                          << std::endl;
        }

       private:
        const char* label_;
        std::chrono::high_resolution_clock::time_point start_;
};

#endif
