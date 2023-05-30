#pragma once
#include <type_traits>
#include <vector>

#include "types.hpp"

template <class DERIVED>
class QuantumState {
    // Prevent inheritance like `class Derived : public QuantumState<Fake>`.
    // When a class deriving this class is instantiated, this constructor is called.
    // If the derived class is not a subclass of QuantumState, the derived class cannot access
    // this constructor because it can only be accessed by DERIVED and compilation fails.
    QuantumState() = default;
    friend DERIVED;

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

    virtual DERIVED& operator+=(const DERIVED& state) = 0;
};
