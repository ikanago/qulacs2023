#pragma once
#include <vector>

#include "types.hpp"

template <Runtime RUNTIME>
class StateVector {
    UINT _n_qubits;
    ITYPE _dim;
    std::vector<Complex> _amplitudes;

public:
    explicit StateVector(UINT n_qubits);

    static StateVector computational_basis(UINT n_qubits, UINT index);

    static StateVector Haar_random_state(UINT n_qubits);

    UINT n_qubits() const noexcept;

    ITYPE dim() const noexcept;

    const std::vector<Complex>& amplitudes() const noexcept;

    double compute_squared_norm() const noexcept;

    // double get_zero_probability() const;

    // double get_marginal_probability(std::vector<UINT>
    // measured_values ) const;

    // double get_entropy() const;

    // double normalize();

    void add_state(const StateVector& state);

    Complex& operator[](UINT index);
};

template class StateVector<Runtime::CPU>;
