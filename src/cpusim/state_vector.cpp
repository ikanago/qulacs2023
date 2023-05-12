#include <core/exceptions.hpp>
#include <core/state_vector.hpp>
#include <core/types.hpp>

#include "init.hpp"

template <>
StateVector<Runtime::CPU>::StateVector(UINT n_qubits)
    : _n_qubits(n_qubits), _dim(1 << n_qubits), _amplitudes(init_zero_state(n_qubits)) {}

template <>
StateVector<Runtime::CPU> StateVector<Runtime::CPU>::computational_basis(
    UINT n_qubits, UINT basis
) {
    if (basis >= 1 << n_qubits) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::set_computational_basis(ITYPE): "
            "index of "
            "computational basis must be smaller than 2^n_qubit"
        );
    }

    StateVector<Runtime::CPU> state(n_qubits);
    state._amplitudes[basis] = 1.0;
    return state;
}

template <>
StateVector<Runtime::CPU> StateVector<Runtime::CPU>::Haar_random_state(UINT n_qubits) {
    StateVector<Runtime::CPU> state(n_qubits);
    state._amplitudes = init_Haar_random_state(n_qubits);
    return state;
}

template <>
UINT StateVector<Runtime::CPU>::n_qubits() const noexcept {
    return this->_n_qubits;
}

template <>
ITYPE StateVector<Runtime::CPU>::dim() const noexcept {
    return this->_dim;
}

template <>
const std::vector<Complex>& StateVector<Runtime::CPU>::amplitudes() const noexcept {
    return this->_amplitudes;
}

template <>
double StateVector<Runtime::CPU>::compute_squared_norm() const noexcept {
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

template <>
Complex& StateVector<Runtime::CPU>::operator[](UINT index) {
    if (index >= this->_dim) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::operator[]: "
            "index of must be smaller than 2^n_qubits"
        );
    }
    return this->_amplitudes[index];
}
