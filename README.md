# Capital‑Gamma

A **high‑performance quantitative‑finance prototype**:  
*Monte‑Carlo option valuation* **+** *low‑latency trading‑flow simulation* in modern **C++17**, with optional Python bindings.

---

## Key Features

### Pricing / Risk
| Engine | Detail |
|--------|--------|
| **Monte‑Carlo European option pricer** | Geometric Brownian Motion paths, deterministic seeding, C++ templates for payoff functors |
| Planned | Black‑Scholes analytic, Asian/barrier payoffs, variance‑reduction schemes |

### Trading‑system Simulation
| Component | Purpose |
|-----------|---------|
| **Lock‑free ring buffer** (`RingBuffer<T,N>`) | Single‑producer/single‑consumer queue that avoids mutex contention (cache‑aligned, pow‑2 size) |
| **In‑memory time‑series DB** (`TimeSeriesDB`) | Records nanosecond timestamps, then prints min/avg/max latency stats |
| **ScopedTimer** | RAII micro‑benchmark helper for any code block |
| **Flow demo** (`src/main.cpp`) | MarketData → DataTransformer → OrderRouter path; compare ring‑buffer vs. std::vector pipeline |

### Tooling
* **CMake 3.15+** build, Ninja, clang‑format/black linters  
* **pybind11** bindings (currently instruments layer)  
* **GitHub Actions** CI, Dockerfile for reproducible builds  
* Unit tests (GoogleTest + pytest)

---

## Quick Start

### Prerequisites
```bash
# Ubuntu
sudo apt install g++-12 cmake ninja-build python3-dev
pip install -r requirements.txt   # black, pytest, pybind11
```

### Build & Run
```bash
git clone https://github.com/<you>/Capital-Gamma.git
cd Capital-Gamma
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j

# run C++ demo (trading flow + timer stats)
./src/capital-gamma
```

### Build Python wheels
```bash
cmake --build . --target capgampy
pip install ./python      # installs capgampy.<hash>.so
```

---

## Usage Examples

### 1. Monte‑Carlo Option Price
```cpp
#include <capgam/engine/mc_option_valuation.hpp>
#include <capgam/instruments/payoffs.hpp>

int main() {
    OptionInfo opt{std::make_unique<CallPayoff>(100.0), 1.0};
    MCOptionValuation pricer{std::move(opt), 252, 0.2, 0.05};
    double px = pricer.calc_price(105.0, 1'000'000, 42u);
    std::cout << "Option = " << px << "\n";
}
```

### 2. Lock‑free Ring Buffer
```cpp
constexpr std::size_t N = 64;
RingBuffer<MarketData,N> rb;

MarketData tick{get_now(), 100.1, 100.2, 100.15};
bool ok = rb.push(tick);          // producer
MarketData out;
if (rb.pop(out)) { /* consume */ }
```

### 3. End‑to‑End Flow Timing
```cpp
{
    ScopedTimer t{"Tick‑pipeline"};
    ring_buffer();     // defined in src/main.cpp
}
```
Console output:
```
processing 5 000 ticks...
Tick‑pipeline took 812µs
min latency: 112ns · max: 425ns · avg: 172ns
```

*(Numbers depend on CPU; shown for illustration.)*

---

## Project Structure
```
include/capgam/
├── common/          # utilities (ScopedTimer)
├── core/            # ring buffer, time‑series DB, message structs
├── engine/          # option‑pricing algorithms
├── instruments/     # payoffs, option metadata
├── models/          # stochastic price generators
└── ...
src/                 # implementations + main demo
bindings/            # pybind11 glue code
test/                # gtest & pytest suites
Dockerfile           # dev container
```

---

## Benchmarks

| Workload | Threads | Latency (µs) | Notes |
|----------|---------|--------------|-------|
| 5 000 ticks via ring buffer | 1P‑1C | **0.81** | Apple M1 Max, Clang 17 ‑O3 |
| Same via `std::vector` push_back | 1 thread | 4.12 | ~5× slower |

*(Run `./bench/run.sh` after building with `-DCMAKE_BUILD_TYPE=Release`.)*

---

## Roadmap
- Python exposure for `core` & `engine`
- Integration with ZeroMQ / FIX for real‑time feeds
- SIMD & thread‑pool Monte‑Carlo
- Code generation for GPU kernels (CUDA)
- Grafana dashboard for latency DB

---

## Contributing & License
Please read **CONTRIBUTING.md** before opening issues/PRs.  
Licensed under the **MIT License** (see LICENSE.md).

---

> *Capital‑Gamma strives to be a showcase of low‑latency systems + derivatives pricing techniques—all in one repository.*  
> Contributions are welcome!
