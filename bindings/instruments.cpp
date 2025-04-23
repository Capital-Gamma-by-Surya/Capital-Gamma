#include <pybind11/pybind11.h>

#include <capgam/instruments/option_info.hpp>
#include <capgam/instruments/payoffs.hpp>

namespace py = pybind11;

void bind_instruments(py::module_ &m) {
    py::class_<CallPayoff>(m, "CallPayOff")
        .def(py::init<double>(),
             "Constructs a CallPayOff with the given strike_price.")
        .def("payoff", &CallPayoff::payoff,
             "Returns payoff value for a given spot.");

    py::class_<PutPayoff>(m, "PutPayOff")
        .def(py::init<double>(),
             "Constructs a PutPayOff with the given strike_price")
        .def("payoff", &PutPayoff::payoff,
             "Returns payoff value for a given spot.");

    py::class_<OptionInfo>(m, "OptionInfo")
        .def(py::init([](const CallPayoff &cp, double strike) {
                 return std::make_unique<OptionInfo>(
                     std::make_unique<CallPayoff>(cp), strike);
             }),
             "Constructs an OptionInfo object with given Payoff object and "
             "time_to_exp")
        .def("payoff", &OptionInfo::payoff,
             "Returns payoff values for a given spot.")
        .def("get_time_to_exp", &OptionInfo::get_time_to_exp,
             "Returns time to expiry for given option.");
}
