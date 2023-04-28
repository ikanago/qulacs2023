#include "init_fill.hpp"

#include <vector>

std::vector<Complex> init_zero_state(UINT n_qubits) {
    UINT dim = 1 << n_qubits;
    std::vector<Complex> amplitudes(dim, 0.0);
    amplitudes[0] = 1.0;
    return amplitudes;
}
