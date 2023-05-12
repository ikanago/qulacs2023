#include <cmath>
#include <complex>
#include <core/types.hpp>
#include <core/update_ops.hpp>

void rx_gate(UINT target_qubit_index, double angle, StateVector<Runtime::CPU>& state) {
    const ITYPE loop_dim = state.dim() / 2;
    const ITYPE mask = (1ULL << target_qubit_index);
    const ITYPE mask_low = mask - 1;
    const ITYPE mask_high = ~mask_low;
    angle /= 2.0;

    ITYPE state_index = 0;
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (state_index = 0; state_index < loop_dim; ++state_index) {
        const ITYPE basis_0 = (state_index & mask_low) + ((state_index & mask_high) << 1);
        const ITYPE basis_1 = basis_0 + mask;

        // fetch values
        const Complex cval_0 = state[basis_0];
        const Complex cval_1 = state[basis_1];

        // set values
        state[basis_0] = cos(angle) * cval_0 - sin(angle) * 1.0i * cval_1;
        state[basis_1] = -1.0i * sin(angle) * cval_0 + cos(angle) * cval_1;
    }
}
