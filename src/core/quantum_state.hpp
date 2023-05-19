#pragma once
#include <type_traits>
#include <vector>

#include "types.hpp"

class QuantumStateBase {
public:
    virtual UINT n_qubits() const noexcept = 0;

    virtual ITYPE dim() const noexcept = 0;

    virtual const std::vector<Complex>& amplitudes() const noexcept = 0;

    virtual double compute_squared_norm() const noexcept = 0;

    // double get_zero_probability() const;

    // double get_marginal_probability(std::vector<UINT>
    // measured_values ) const;

    // double get_entropy() const;

    // double normalize();

    virtual Complex& operator[](UINT index) = 0;
};
