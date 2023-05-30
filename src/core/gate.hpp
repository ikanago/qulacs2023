#pragma once

#include <core/types.hpp>
#include <variant>

#include "quantum_state.hpp"

template <class T, class S>
class QuantumGate {
public:
    virtual void update_quantum_state(QuantumStateBase<S>& state) const = 0;
};
