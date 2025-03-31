#include <pybind11/pybind11.h>

#include <capgam/instruments/payoffs.hpp>

namespace py = pybind11;

PYBIND11_MODULE(capgampy, m) {
    py::class_<CallPayoff>(m, "CallPayOff")
        .def(py::init<double>(),
             "Constructs a CallPayOff with the given strike_price")
        .def("payoff", &CallPayoff::payoff,
             "Returns payoff value for a given price");

    py::class_<PutPayoff>(m, "PutPayOff")
        .def(py::init<double>(),
             "Constructs a PutPayOff with the given strike_price")
        .def("payoff", &PutPayoff::payoff,
             "Returns payoff value for a given price.");
}
