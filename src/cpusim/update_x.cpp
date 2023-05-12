#include <core/types.hpp>
#include <core/update_ops.hpp>

// template <Runtime RUNTIME>
void x_gate(UINT target_qubit_index, StateVector<Runtime::CPU>& state) {
    const ITYPE mask = (1ULL << target_qubit_index);
    const ITYPE mask_low = mask - 1;
    const ITYPE mask_high = ~mask_low;
    if (target_qubit_index == 0) {
        ITYPE basis_index = 0;
        // #pragma omp parallel for
        for (basis_index = 0; basis_index < state.dim(); basis_index += 2) {
            Complex temp = state[basis_index];
            state[basis_index] = state[basis_index + 1];
            state[basis_index + 1] = temp;
        }
    } else {
        // #pragma omp parallel for
        ITYPE state_index = 0;
        const ITYPE loop_dim = state.dim() / 2;
        for (state_index = 0; state_index < loop_dim; state_index += 2) {
            const ITYPE basis_index_0 = (state_index & mask_low) + ((state_index & mask_high) << 1);
            const ITYPE basis_index_1 = basis_index_0 + mask;
            const Complex temp0 = state[basis_index_0];
            const Complex temp1 = state[basis_index_0 + 1];

            state[basis_index_0] = state[basis_index_1];
            state[basis_index_0 + 1] = state[basis_index_1 + 1];
            state[basis_index_1] = temp0;
            state[basis_index_1 + 1] = temp1;
        }
    }
}
