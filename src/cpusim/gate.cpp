#include "gate.hpp"

#include <variant>

#include "gate_named_one.hpp"

template <>
void QuantumGate<Runtime::CPU>::update_quantum_state(StateVector<Runtime::CPU>& state) const {
    std::visit([&](auto&& gate) { gate.update_quantum_state(state); }, this->_gate);
}
