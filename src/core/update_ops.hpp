#pragma once

#include <cpusim/state_vector.hpp>

#include "types.hpp"

// template <Runtime RUNTIME>
void x_gate(UINT target, StateVector<Runtime::CPU>& state);

void rx_gate(UINT target, double angle, StateVector<Runtime::CPU>& state);
