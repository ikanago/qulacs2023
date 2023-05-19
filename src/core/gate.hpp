#pragma once

#include <core/types.hpp>
#include <variant>

#include "gate_named_one.hpp"
#include "quantum_state.hpp"

class QuantumGate {
    using GateKind = std::variant<XGate, RXGate>;
    GateKind _gate;

    explicit QuantumGate(const GateKind& gate) : _gate(gate) {}

public:
    static QuantumGate X(UINT target) { return QuantumGate(XGate(target)); }

    void update_quantum_state(StateVectorCpu& state) const;
};
