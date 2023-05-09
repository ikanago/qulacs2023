#include <gtest/gtest.h>

#include <core/types.hpp>
#include <cpusim/state_vector.hpp>

#include "util.hpp"

const double eps = 1e-12;

TEST(StateTest, HaarRandomStateNorm) {
    const UINT max_tries = 20;
    for (UINT n = 1; n <= max_tries; n++) {
        const auto state = StateVector<Runtime::CPU>::Haar_random_state(n);
        ASSERT_NEAR(state.compute_squared_norm(), 1., eps);
    }
}

TEST(StateVectorTest, AddState) {
    const uint64_t n = 10;
    auto state1 = StateVector<Runtime::CPU>::Haar_random_state(n);
    auto state2 = StateVector<Runtime::CPU>::Haar_random_state(n);

    const int64_t dim = 1ULL << n;
    auto state_vector1 = std::vector<Complex>(state1.amplitudes());
    auto state_vector2 = std::vector<Complex>(state2.amplitudes());

    state1.add_state(state2);

    for (int64_t i = 0; i < dim; ++i) {
        ASSERT_NEAR(
            state1[i].real(), state_vector1[i].real() + state_vector2[i].real(), eps
        );
        ASSERT_NEAR(
            state1[i].imag(), state_vector1[i].imag() + state_vector2[i].imag(), eps
        );
    }
}
