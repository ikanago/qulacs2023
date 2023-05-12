#pragma once

#include <vector>

#include "gate.hpp"
#include "types.hpp"

template <Runtime RUNTIME>
class QuantumCircuit {
    UINT _n_qubits;
    std::vector<QuantumGate<RUNTIME>> _gates;

public:
    explicit QuantumCircuit(UINT n_qubits) : _n_qubits(n_qubits) {}

    void add_gate(const QuantumGate<RUNTIME>& gate) { this->_gates.push_back(gate); }

    void update_quantum_state(StateVector<RUNTIME>& state) const {
        for (const auto& gate : this->_gates) gate.update_quantum_state(state);
    }
};
