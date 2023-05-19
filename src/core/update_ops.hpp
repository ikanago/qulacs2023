#pragma once

#include <cpusim/state_vector.hpp>

#include "types.hpp"

void x_gate(UINT target, StateVectorCpu& state);

void rx_gate(UINT target, double angle, StateVectorCpu& state);
