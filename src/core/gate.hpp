#pragma once

#include <core/types.hpp>
#include <variant>

#include "gate_named_one.hpp"
#include "state_vector.hpp"

template <Runtime RUNTIME>
class QuantumGate {
    using GateKind = std::variant<XGate<RUNTIME>, RXGate<RUNTIME>>;
    GateKind _gate;

    explicit QuantumGate(const GateKind& gate) : _gate(gate) {}

public:
    static QuantumGate X(UINT target) { return QuantumGate<RUNTIME>(XGate<RUNTIME>(target)); }

    void update_quantum_state(StateVector<RUNTIME>& state) const;
};

template class QuantumGate<Runtime::CPU>;
