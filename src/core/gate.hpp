#pragma once

#include <core/types.hpp>
#include <variant>

#include "quantum_state.hpp"

template <class DERIVED, class S>
class QuantumGate {
    QuantumGate() = default;
    friend DERIVED;

public:
    virtual void update_quantum_state(QuantumState<S>& state) const = 0;
};
