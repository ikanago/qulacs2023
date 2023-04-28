#include <gtest/gtest.h>

#include <core/types.hpp>
#include <cpusim/state_vector.hpp>

#define ASSERT_STATE_NEAR(state, other, eps) \
    ASSERT_PRED_FORMAT3(_assert_state_near, state, other, eps)

template <Runtime RUNTIME>
static testing::AssertionResult _assert_state_near(
    const char* state1_name, const char* state2_name, const char* eps_name,
    const StateVector<RUNTIME>& state1, const StateVector<RUNTIME>& state2, const double eps
) {
    if (state1.dim() != state2.dim()) {
        return testing::AssertionFailure()
               << "The dimension is different\nDimension of " << state1_name << " is " << state1.dim
               << ",\n"
               << "Dimension of " << state2_name << " is " << state2.dim << ".";
    }

    for (ITYPE i = 0; i < state1.dim; i++) {
        const double real_diff =
            std::fabs(state1.amplitudes()[i].real() - state2.amplitudes()[i].real());
        if (real_diff > eps) {
            return testing::AssertionFailure()
                   << "The difference between " << i << "-th real part of " << state1_name
                   << " and " << state2_name << " is " << real_diff << ", which exceeds " << eps
                   << ", where\n"
                   << state1_name << " evaluates to " << state1.amplitudes()[i].real() << ",\n"
                   << state2_name << " evaluates to " << state2.amplitudes()[i].real() << ", and\n"
                   << eps_name << " evaluates to " << eps << ".";
        }

        const double imag_diff =
            std::fabs(state1.amplitudes()[i].real() - state2.amplitudes()[i].real());
        if (imag_diff > eps) {
            return testing::AssertionFailure()
                   << "The difference between " << i << "-th imaginary part of " << state1_name
                   << " and " << state2_name << " is " << imag_diff << ", which exceeds " << eps
                   << ", where\n"
                   << state1_name << " evaluates to " << state1.amplitudes()[i].imag() << ",\n"
                   << state2_name << " evaluates to " << state2.amplitudes()[i].imag() << ", and\n"
                   << eps_name << " evaluates to " << eps << ".";
        }
    }

    return testing::AssertionSuccess();
}