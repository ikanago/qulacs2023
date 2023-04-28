#include "init_random.hpp"

#include <vector>

#include "random.hpp"

std::vector<Complex> init_Haar_random_state(UINT n_qubits) {
    Random rng;
    const ITYPE dim = 1ULL << n_qubits;
    std::vector<Complex> state(dim);
    double norm = 0.0;
    for (UINT i = 0; i < dim; ++i) {
        state[i] = Complex(rng.uniform(), rng.uniform());
        norm += std::norm(state[i]);
    }

    const auto norm_sqrt = std::sqrt(norm);
    for (UINT i = 0; i < dim; ++i) {
        state[i] /= norm_sqrt;
    }
    return state;
}
