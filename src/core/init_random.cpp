#include "init_random.hpp"

#include <cstdint>
#include <vector>

#include "random.hpp"

std::vector<Complex> init_Haar_random_state(std::uint64_t n_qubits) {
    Random rng;
    std::vector<Complex> state(1ULL << n_qubits);
    double norm_squared = 0.0;
    for (std::uint64_t i = 0; i < (1ULL << n_qubits); ++i) {
        state[i] = Complex(rng.uniform(), rng.uniform());
        norm_squared += std::pow(std::norm(state[i]), 2.0);
    }

    const double norm = std::sqrt(norm_squared);
    for (std::uint64_t i = 0; i < (1ULL << n_qubits); ++i) {
        state[i] /= norm;
    }
    return state;
}
