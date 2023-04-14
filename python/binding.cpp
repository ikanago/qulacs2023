#include <pybind11/pybind11.h>

#include <cpusim/state_vector.hpp>

PYBIND11_MODULE(qulacs, m)
{
    pybind11::class_<StateVector>(m, "StateVector");
}
