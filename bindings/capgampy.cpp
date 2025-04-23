#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void bind_instruments(py::module_ &);

PYBIND11_MODULE(capgampy, m) {
    auto instruments =
        m.def_submodule("instruments", "Financial instruments module");
    bind_instruments(instruments);
}
