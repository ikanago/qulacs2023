#include "state_vector.hpp"

#include <cstdint>

#include "../core/init_fill.hpp"
#include "./exceptions.hpp"

template <Runtime RUNTIME>
StateVector<RUNTIME>::StateVector(std::uint64_t n_qubits)
    : n_qubits_(n_qubits),
      dim_(1 << n_qubits),
      amplitudes(init_zero_state(n_qubits)) {}

template <Runtime RUNTIME>
StateVector<RUNTIME> StateVector<RUNTIME>::computational_basis(
    std::uint64_t n_qubits, std::uint64_t basis
) {
    if (basis >= 1 << n_qubits) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::set_computational_basis(ITYPE): "
            "index of "
            "computational basis must be smaller than 2^qubit_count"
        );
    }

    StateVector<RUNTIME> state(n_qubits);
    state.amplitudes[basis] = 1.0;
    return state;
}

template <Runtime RUNTIME>
std::uint64_t StateVector<RUNTIME>::n_qubits() const noexcept {
    return this->n_qubits_;
}

template <Runtime RUNTIME>
std::int64_t StateVector<RUNTIME>::dim() const noexcept {
    return this->dim_;
}

template <>
void StateVector<Runtime::CPU>::add_state(const StateVector& state) {
    for (std::int64_t i = 0; i < this->dim_; i++) {
        this->amplitudes[i] += state.amplitudes[i];
    }
}
