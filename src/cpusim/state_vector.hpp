#pragma once
#include <core/types.hpp>
#include <vector>

enum class Runtime { CPU };

template <Runtime RUNTIME>
class StateVector {
    UINT n_qubits_;
    ITYPE dim_;
    std::vector<Complex> amplitudes_;

public:
    StateVector(UINT n_qubits);

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
};

template class StateVector<Runtime::CPU>;
