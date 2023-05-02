#pragma once

#include <core/types.hpp>
#include <variant>

#include "gate_named_one.hpp"
#include "state_vector.hpp"

template <Runtime RUNTIME>
class QuantumGate {
    std::variant<X<RUNTIME>, RX<RUNTIME>> _gate;
};
