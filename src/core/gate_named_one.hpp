#pragma once

#include <core/types.hpp>
#include <core/update_ops.hpp>

#include "gate.hpp"

template <class S>
class XGate : public QuantumGate<XGate<S>, S> {
    UINT _target;

public:
    explicit XGate(UINT target) : _target(target) {}

    void update_quantum_state(QuantumStateBase<S>& state) const override {
        S& state_derived = static_cast<S&>(state);
        x_gate(this->_target, state_derived);
    }
};

class RXGate {
    UINT _target;
    double _angle;

public:
    void update_quantum_state(StateVectorCpu& state) const {
        rx_gate(this->_target, this->_angle, state);
    }
};
