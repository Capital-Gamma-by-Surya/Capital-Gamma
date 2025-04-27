# Capital-Gamma

Monte-Carlo Option Pricing library in **modern C++17** with optional **Python bindings**.

## Table of Contents
1. [Features](#features)  
2. [Getting Started](#getting-started)  
3. [Usage Examples](#usage-examples)  
4. [Project Structure](#project-structure)  
5. [Running the Tests](#running-the-tests)  
6. [Roadmap](#roadmap)  
7. [Contributing](#contributing)  
8. [License](#license)  
9. [Disclaimer](#disclaimer)  

## Features
- **Vanilla European option pricing** via Monte-Carlo simulation  
- Modular design: `engine`, `models`, and `instruments` layers  
- Two payoff types out-of-the-box: **Call** and **Put**  
- Geometric Brownian Motion equity path generator  
- Deterministic seeding for reproducible research  
- Python interoperability through **pybind11**  
- Continuous integration with GitHub Actions & Docker  
- Unit tests for C++ (GoogleTest) and Python (pytest)  

## Getting Started

### Prerequisites
- A C++17 compiler (GCC ≥ 10, Clang ≥ 13, or MSVC 2022)  
- **CMake** ≥ 3.15 & **Ninja** build system  
- **Python** ≥ 3.9 + `pip install -r requirements.txt`  
- (Optional) **Docker 24.04** for a turnkey environment  

### Build & Install — C++
```bash
git clone https://github.com/<your-fork>/Capital-Gamma.git
cd Capital-Gamma
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j
sudo cmake --install .
```

### Build the Python bindings
```bash
# still inside build/
cmake --build . --target capgampy -j
pip install ./python      # installs the compiled capgampy.*.so
```

### Docker quick-start
```bash
docker build -t capgam:latest .
docker run --rm -it capgam:latest bash
```

## Usage Examples

### C++
```cpp
#include <capgam/engine/mc_option_valuation.hpp>
#include <capgam/instruments/payoffs.hpp>
#include <memory>
#include <iostream>

int main() {
    OptionInfo opt{std::make_unique<CallPayoff>(100.0), 1.0};  // 1-year expiry
    MCOptionValuation pricer{std::move(opt), 252, 0.2, 0.05};

    double price = pricer.calc_price(105.0, 1'000'000, 42u);
    std::cout << "Option price = " << price << "\n";
}
```

### Python
```python
from capgampy.instruments import CallPayOff, OptionInfo
# TODO: expose engine bindings; currently only instruments are bound

opt = OptionInfo(CallPayOff(100.0), 1.0)
# pricer = capgampy.engine.MCOptionValuation(opt, 252, 0.2, 0.05)
# price = pricer.calc_price(105.0, 1_000_000, 42)
```

## Project Structure
```
Capital-Gamma/
├── include/capgam/          # Public headers
│   ├── instruments/         # Payoff abstractions
│   ├── models/              # Stochastic processes
│   └── engine/              # Valuation algorithms
├── src/                     # Implementations
├── bindings/                # pybind11 glue
├── test/                    # Unit tests
├── Dockerfile               # Dev container
└── CMakeLists.txt           # Build orchestrator
```

## Running the Tests

### C++
```bash
cmake -DENABLE_TESTING=ON ..
cmake --build . --target test
ctest
```

### Python
```bash
pytest test/bindings
```

## Roadmap
- Expose `engine` and `models` namespaces to Python  
- Analytical Black-Scholes engine for benchmarking  
- Asian, barrier & digital option payoffs  
- Quasi-Monte Carlo variance reduction  
- Doxygen + Sphinx documentation site  

## Contributing
We welcome pull requests!  
1. Fork the repo and create a feature branch.  
2. Run `clang-format -i` and `black` before committing.  
3. Make sure `ctest` and `pytest` pass.  
4. Open a PR with a clear description of your change.  

## License
*License to be decided — defaulting to MIT for now.*

## Disclaimer
This software is for **educational and research purposes only** and does not constitute investment advice.  
Use at your own risk.
