# Capital‑Gamma
[![CI](https://github.com/Capital-Gamma-by-Surya/Capital-Gamma/actions/workflows/ci.yml/badge.svg)](https://github.com/Capital-Gamma-by-Surya/Capital-Gamma/actions/workflows/ci.yml)
![Pre-Release](https://img.shields.io/github/release/Capital-Gamma-by-Surya/Capital-Gamma?include_prereleases&label=latest%20pre-release)
![Lang](https://img.shields.io/github/languages/top/Capital-Gamma-by-Surya/Capital-Gamma)

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
Tick‑pipeline took 544µs
min latency: 125ns · max: 13µs · avg: 840ns
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

## Benchmarks  <sup>Apple M4 Base · Clang 17 -O3 · 5 000 ticks</sup>

| Pipeline                           | Avg Latency | Min Latency | Max Latency | End-to-End Latency<sup>*</sup> | Total Processing Time |
|-----------------------------------|------------:|------------:|------------:|------------------------------:|----------------------:|
| **Lock-free ring-buffer**         | **0.807 µs** | 0.125 µs | 21.9 µs | **4.04 ms** | 0.544 ms |
| `std::vector` push / pop          | 140.8 µs | — | — | 703.8 ms | **0.281 ms** |

<sup>*Sum of per-tick latencies (≈ area under latency curve).</sup>

### How to read these numbers
* **Latency** measures the time between a tick’s arrival in the buffer and its routing to the (dummy) order router.
Ring buffer slashes average latency by 175× versus a raw std::vector queue (0.8 µs vs 140 µs).

* **Total processing time** is the wall-clock time to run the full 5 000-tick demo.
The vector path is ~2× faster here because it avoids the atomic counters used for the lock-free queue, but it pays for that with far higher per-tick latency and a huge long-tail (703 ms vs 4 ms).

* **Take-away** For latency-sensitive trading flows, the lock-free ring buffer delivers sub-microsecond service times and tight tail latency, at the cost of a small constant-time overhead on the full batch.

*(Run `./build/cap_gam_hello` after building with `-DCMAKE_BUILD_TYPE=Release`.)*

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
