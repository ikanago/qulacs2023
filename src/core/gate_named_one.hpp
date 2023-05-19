#pragma once

#include <core/types.hpp>
#include <core/update_ops.hpp>

class XGate {
    UINT _target;

public:
    XGate(UINT target) : _target(target) {}

    void update_quantum_state(StateVectorCpu& state) const { x_gate(this->_target, state); }
};

class RXGate {
    UINT _target;
    double _angle;

public:
    void update_quantum_state(StateVectorCpu& state) const {
        rx_gate(this->_target, this->_angle, state);
    }
};
