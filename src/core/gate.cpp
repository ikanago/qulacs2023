#include "gate.hpp"

#include <variant>

#include "gate_named_one.hpp"
#include "quantum_state.hpp"

void QuantumGate::update_quantum_state(StateVectorCpu& state) const {
    std::visit([&](auto&& gate) { gate.update_quantum_state(state); }, this->_gate);
}
