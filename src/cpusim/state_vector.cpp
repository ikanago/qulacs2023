#include "state_vector.hpp"

#include <core/init_fill.hpp>
#include <core/init_random.hpp>
#include <core/types.hpp>

#include "exceptions.hpp"

template <Runtime RUNTIME>
StateVector<RUNTIME>::StateVector(UINT n_qubits)
    : n_qubits_(n_qubits), dim_(1 << n_qubits), amplitudes_(init_zero_state(n_qubits)) {}

template <Runtime RUNTIME>
StateVector<RUNTIME> StateVector<RUNTIME>::computational_basis(UINT n_qubits, UINT basis) {
    if (basis >= 1 << n_qubits) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::set_computational_basis(ITYPE): "
            "index of "
            "computational basis must be smaller than 2^qubit_count"
        );
    }

    StateVector<RUNTIME> state(n_qubits);
    state.amplitudes_[basis] = 1.0;
    return state;
}

template <Runtime RUNTIME>
StateVector<RUNTIME> StateVector<RUNTIME>::Haar_random_state(UINT n_qubits) {
    StateVector<RUNTIME> state(n_qubits);
    state.amplitudes_ = init_Haar_random_state(n_qubits);
    return state;
}

template <Runtime RUNTIME>
UINT StateVector<RUNTIME>::n_qubits() const noexcept {
    return this->n_qubits_;
}

template <Runtime RUNTIME>
ITYPE StateVector<RUNTIME>::dim() const noexcept {
    return this->dim_;
}

template <Runtime RUNTIME>
const std::vector<Complex>& StateVector<RUNTIME>::amplitudes() const noexcept {
    return this->amplitudes_;
}

template <Runtime RUNTIME>
double StateVector<RUNTIME>::compute_squared_norm() const noexcept {
    double squared_norm = 0.0;
    for (const auto& amplitude : this->amplitudes_) {
        squared_norm += std::norm(amplitude);
    }
    return squared_norm;
}

template <>
void StateVector<Runtime::CPU>::add_state(const StateVector& state) {
    for (ITYPE i = 0; i < this->dim_; i++) {
        this->amplitudes_[i] += state.amplitudes_[i];
    }
}
