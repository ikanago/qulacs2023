#pragma once

#include <core/types.hpp>
#include <core/update_ops.hpp>

#include "state_vector.hpp"

template <Runtime RUNTIME>
class XGate {
    UINT _target;

public:
    XGate(UINT target) : _target(target) {}

    void update_quantum_state(StateVector<RUNTIME>& state) const { x_gate(this->_target, state); }
};

template <Runtime RUNTIME>
class RXGate {
    UINT _target;
    double _angle;

public:
    void update_quantum_state(StateVector<RUNTIME>& state) const {
        rx_gate(this->_target, this->_angle, state);
    }
};
