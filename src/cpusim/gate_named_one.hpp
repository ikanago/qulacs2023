#pragma once

#include <core/types.hpp>
#include <core/update_ops.hpp>

#include "state_vector.hpp"

template <Runtime RUNTIME>
class X {
    UINT _target;

public:
    void update_quantum_state(StateVector<RUNTIME>& state) const { x_gate(this->_target, state); }
};

template <Runtime RUNTIME>
class RX {
    UINT _target;
    double _angle;

public:
    void update_quantum_state(StateVector<RUNTIME>& state) const {
        rx_gate(this->_target, this->_angle, state);
    }
};
