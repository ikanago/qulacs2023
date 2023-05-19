#include <gtest/gtest.h>

#include <Eigen/Core>
#include <core/gate.hpp>
#include <core/random.hpp>
#include <core/types.hpp>
#include <cpusim/state_vector.hpp>
#include <functional>

#include "util.hpp"

const auto eps = 1e-12;

template <class QuantumGateConstructor>
void run_random_gate_apply(
    UINT n_qubits,
    QuantumGateConstructor constructor,
    std::function<Eigen::MatrixXcd()> matrix_factory
) {
    const auto matrix = matrix_factory();
    const ITYPE dim = 1ULL << n_qubits;
    Random random;

    Eigen::VectorXcd test_state = Eigen::VectorXcd::Zero(dim);
    for (UINT repeat = 0; repeat < 10; repeat++) {
        auto state = StateVectorCpu::Haar_random_state(n_qubits);
        for (ITYPE i = 0; i < dim; i++) test_state[i] = state[i];

        const UINT target = random.int32() % n_qubits;
        auto gate = constructor(target);
        gate.update_quantum_state(state);

        test_state = get_expanded_eigen_matrix_with_identity(target, matrix, n_qubits) * test_state;

        for (ITYPE i = 0; i < dim; i++) {
            ASSERT_NEAR(std::abs(state[i] - test_state[i]), 0, eps);
        }
    }
}

TEST(GateTest, ApplySingleQubitGate) { run_random_gate_apply(5, QuantumGate::X, make_X); }
