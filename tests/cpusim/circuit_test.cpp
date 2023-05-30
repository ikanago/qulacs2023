#include <gtest/gtest.h>

#include <core/circuit.hpp>
#include <core/gate_named_one.hpp>

TEST(CircuitTest, AddGate) {
    QuantumCircuit<StateVectorCpu> circuit(5);
    circuit.X(0);
}
