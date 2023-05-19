#include "state_vector.hpp"

#include <core/exceptions.hpp>
#include <core/types.hpp>
#include <type_traits>

#include "init.hpp"

StateVectorCpu::StateVectorCpu(UINT n_qubits)
    : _n_qubits(n_qubits), _dim(1 << n_qubits), _amplitudes(init_zero_state(n_qubits)) {}

StateVectorCpu StateVectorCpu::computational_basis(UINT n_qubits, UINT basis) {
    if (basis >= 1 << n_qubits) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::set_computational_basis(ITYPE): "
            "index of "
            "computational basis must be smaller than 2^n_qubit"
        );
    }

    StateVectorCpu state(n_qubits);
    state._amplitudes[basis] = 1.0;
    return state;
}

StateVectorCpu StateVectorCpu::Haar_random_state(UINT n_qubits) {
    StateVectorCpu state(n_qubits);
    state._amplitudes = init_Haar_random_state(n_qubits);
    return state;
}

UINT StateVectorCpu::n_qubits() const noexcept { return this->_n_qubits; }

ITYPE StateVectorCpu::dim() const noexcept { return this->_dim; }

const std::vector<Complex>& StateVectorCpu::amplitudes() const noexcept {
    return this->_amplitudes;
}

double StateVectorCpu::compute_squared_norm() const noexcept {
    double squared_norm = 0.0;
    for (const auto& amplitude : this->_amplitudes) {
        squared_norm += std::norm(amplitude);
    }
    return squared_norm;
}

Complex& StateVectorCpu::operator[](UINT index) {
    if (index >= this->_dim) {
        throw MatrixIndexOutOfRangeException(
            "Error: QuantumStateCpu::operator[]: "
            "index of must be smaller than 2^n_qubits"
        );
    }
    return this->_amplitudes[index];
}

StateVectorCpu& StateVectorCpu::operator+=(const StateVectorCpu& state) {
    for (ITYPE i = 0; i < this->_dim; i++) {
        this->_amplitudes[i] += state.amplitudes()[i];
    }
}
