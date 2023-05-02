#include <gtest/gtest.h>

#include <core/random.hpp>
#include <core/types.hpp>
#include <cpusim/gate.hpp>
#include <cpusim/state_vector.hpp>
#include <functional>

#include "util.hpp"

const auto eps = 1e-12;

testing::AssertionResult run_random_gate_apply(std::function<QuantumGate<Runtime::CPU>(UINT)>) {}

TEST(GateTest, ApplySingleQubitGate) {
    const auto X = make_X();
    const UINT n_qubits = 5;
    const UINT dim = 1ULL << n_qubits;
    Random random;

    Eigen::VectorXcd test_state = Eigen::VectorXcd::Zero(dim);
    for (UINT repeat = 0; repeat < 10; ++repeat) {
        auto state = StateVector<Runtime::CPU>::Haar_random_state(n_qubits);
        for (ITYPE i = 0; i < dim; ++i) test_state[i] = state[i];

        auto mat = X;
        UINT target = random.int32() % n_qubits;
        auto gate = QuantumGate<Runtime::CPU>::X(target);
        gate.update_quantum_state(state);

        test_state = get_expanded_eigen_matrix_with_identity(target, mat, n_qubits) * test_state;

        for (ITYPE i = 0; i < dim; ++i) {
            ASSERT_NEAR(std::abs(state[i] - test_state[i]), 0, eps);
        }
    }
}
