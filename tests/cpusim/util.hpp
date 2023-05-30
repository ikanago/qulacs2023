#include <gtest/gtest.h>

#include <Eigen/Core>
#include <core/types.hpp>

static Eigen::MatrixXcd kronecker_product(
    const Eigen::MatrixXcd& lhs, const Eigen::MatrixXcd& rhs
) {
    Eigen::MatrixXcd result(lhs.rows() * rhs.rows(), lhs.cols() * rhs.cols());
    for (int i = 0; i < lhs.cols(); i++) {
        for (int j = 0; j < lhs.rows(); j++) {
            result.block(i * rhs.rows(), j * rhs.cols(), rhs.rows(), rhs.cols()) = lhs(i, j) * rhs;
        }
    }
    return result;
}

static Eigen::MatrixXcd get_expanded_eigen_matrix_with_identity(
    UINT target_qubit_index, const Eigen::MatrixXcd& one_qubit_matrix, UINT qubit_count
) {
    const ITYPE left_dim = 1ULL << target_qubit_index;
    const ITYPE right_dim = 1ULL << (qubit_count - target_qubit_index - 1);
    auto left_identity = Eigen::MatrixXcd::Identity(left_dim, left_dim);
    auto right_identity = Eigen::MatrixXcd::Identity(right_dim, right_dim);
    return kronecker_product(kronecker_product(right_identity, one_qubit_matrix), left_identity);
}

#define ASSERT_STATE_NEAR(state, other, eps) \
    ASSERT_PRED_FORMAT3(_assert_state_near, state, other, eps)

template <Runtime RUNTIME, class T>
static testing::AssertionResult _assert_state_near(
    const char* state1_name,
    const char* state2_name,
    const char* eps_name,
    const QuantumStateBase<T>& state1,
    const QuantumStateBase<T>& state2,
    const double eps
) {
    if (state1.dim() != state2.dim()) {
        return testing::AssertionFailure()
               << "The dimension is different\nDimension of " << state1_name << " is "
               << state1.dim() << ",\n"
               << "Dimension of " << state2_name << " is " << state2.dim() << ".";
    }

    for (ITYPE i = 0; i < state1.dim(); i++) {
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

static Eigen::MatrixXcd make_2x2_matrix(
    const Eigen::dcomplex a00,
    const Eigen::dcomplex a01,
    const Eigen::dcomplex a10,
    const Eigen::dcomplex a11
) {
    Eigen::MatrixXcd m(2, 2);
    m << a00, a01, a10, a11;
    return m;
}

static Eigen::MatrixXcd make_X() { return make_2x2_matrix(0, 1, 1, 0); }
