#pragma once
#include <cstdint>
#include <vector>

#include "types.hpp"

enum class Runtime { CPU };

template <Runtime RUNTIME>
class StateVector {
    std::uint64_t n_qubits_;
    std::int64_t dim_;
    std::vector<Complex> amplitudes;

public:
    StateVector(std::uint64_t n_qubits);

    static StateVector computational_basis(
        std::uint64_t n_qubits, std::uint64_t index
    );

    // static StateVector random_state(std::uint64_t n_qubits);

    std::uint64_t n_qubits() const noexcept;

    std::int64_t dim() const noexcept;

    // double get_zero_probability() const;

    // double get_marginal_probability(std::vector<std::uint64_t>
    // measured_values ) const;

    // double get_entropy() const;

    // double normalize();

    void add_state(const StateVector& state);
};

template class StateVector<Runtime::CPU>;
