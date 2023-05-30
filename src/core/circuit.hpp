#pragma once

#include <vector>

#include "gate.hpp"
#include "gate_named_one.hpp"
#include "types.hpp"

template <class S>
class QuantumCircuit {
    using GateKind = std::variant<XGate<S>>;

    UINT _n_qubits;
    std::vector<GateKind> _gates;

public:
    explicit QuantumCircuit(UINT n_qubits) : _n_qubits(n_qubits) {}

    void X(UINT target) {
        this->_gates.push_back(XGate<S>(target));
    }

    void update_quantum_state(QuantumState<S>& state) const {
        for (const auto& gate : this->_gates) {
            std::visit([&](auto&& gate) { gate.update_quantum_state(state); }, this->_gate);
        }
    }
};
