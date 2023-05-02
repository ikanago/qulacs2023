#include "state_vector.hpp"

#include <core/init_fill.hpp>
#include <core/init_random.hpp>
#include <core/types.hpp>

#include "exceptions.hpp"

template <Runtime RUNTIME>
StateVector<RUNTIME>::StateVector(UINT n_qubits)
    : _n_qubits(n_qubits), _dim(1 << n_qubits), _amplitudes(init_zero_state(n_qubits)) {}

template <Runtime RUNTIME>
StateVector<RUNTIME> StateVector<RUNTIME>::computational_basis(UINT n_qubits, UINT basis) {
    if (basis >= 1 << n_qubits) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::set_computational_basis(ITYPE): "
            "index of "
            "computational basis must be smaller than 2^n_qubit"
        );
    }

    StateVector<RUNTIME> state(n_qubits);
    state._amplitudes[basis] = 1.0;
    return state;
}

template <Runtime RUNTIME>
StateVector<RUNTIME> StateVector<RUNTIME>::Haar_random_state(UINT n_qubits) {
    StateVector<RUNTIME> state(n_qubits);
    state._amplitudes = init_Haar_random_state(n_qubits);
    return state;
}

template <Runtime RUNTIME>
UINT StateVector<RUNTIME>::n_qubits() const noexcept {
    return this->_n_qubits;
}

template <Runtime RUNTIME>
ITYPE StateVector<RUNTIME>::dim() const noexcept {
    return this->_dim;
}

template <Runtime RUNTIME>
const std::vector<Complex>& StateVector<RUNTIME>::amplitudes() const noexcept {
    return this->_amplitudes;
}

template <Runtime RUNTIME>
double StateVector<RUNTIME>::compute_squared_norm() const noexcept {
    double squared_norm = 0.0;
    for (const auto& amplitude : this->_amplitudes) {
        squared_norm += std::norm(amplitude);
    }
    return squared_norm;
}

template <>
void StateVector<Runtime::CPU>::add_state(const StateVector& state) {
    for (ITYPE i = 0; i < this->_dim; i++) {
        this->_amplitudes[i] += state._amplitudes[i];
    }
}

template <Runtime RUNTIME>
Complex& StateVector<RUNTIME>::operator[](UINT index) {
    if (index >= this->_dim) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::operator[]: "
            "index of must be smaller than 2^n_qubits"
        );
    }
    return this->_amplitudes[index];
}
