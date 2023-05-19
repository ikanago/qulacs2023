#pragma once

#include <core/quantum_state.hpp>
#include <core/types.hpp>

class StateVectorCpu : public QuantumStateBase {
    UINT _n_qubits;
    ITYPE _dim;
    std::vector<Complex> _amplitudes;

public:
    StateVectorCpu(UINT n_qubits);

    static StateVectorCpu computational_basis(UINT n_qubits, UINT basis);

    static StateVectorCpu Haar_random_state(UINT n_qubits);

    UINT n_qubits() const noexcept override;

    ITYPE dim() const noexcept override;

    const std::vector<Complex>& amplitudes() const noexcept override;

    double compute_squared_norm() const noexcept override;

    Complex& operator[](UINT index) override;

    StateVectorCpu& operator+=(const StateVectorCpu& state);
};
