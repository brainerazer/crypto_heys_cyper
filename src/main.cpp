#include "io.h"
#include "byte_utils.h"
#include "heys.h"

#include <iostream>
#include <omp.h>


int main()
{
    const size_t SIZE = 0x10000; // = 65536

    const size_t STEP = 16;

    std::vector<uint16_t> ab_count(SIZE * SIZE, 0);

    std::vector<block_t> round_keys = {0x0, 0x0, 0x0, 0x0, 0x0}; // len == 5

    size_t steps_completed = 0;
    std::cout << "Max steps = " << SIZE / STEP << std::endl;

    #pragma omp parallel for
    for(size_t a = 1; a < SIZE; a++) {
        for (size_t plaintext = 0; plaintext < SIZE; plaintext++) {
            block_t ct = cipher_rounds(plaintext, round_keys);
            block_t ct_a = cipher_rounds(plaintext ^ a, round_keys);

            block_t b = ct ^ ct_a;

            #pragma omp atomic
            ab_count[merge_blocks(a, b)] = ab_count[merge_blocks(a, b)] + 1;
        }


        if(a % STEP == 0) {
            #pragma omp atomic
            ++steps_completed;

            #pragma omp critical
            std::cout << "Progress: " << steps_completed << " of " << SIZE / STEP << std::endl;
        }
    }

    size_t max = 0;
    uint32_t max_index = 0;

    for(size_t i = 0; i < SIZE * SIZE; ++i) {
        if(ab_count[i] > max) {
            max = ab_count[i];
            max_index = i;
        }
    }

    std::cout << "Max prob: " << max << "/" << SIZE * SIZE << ", on index " << max_index << std::endl;
    std::cout << "a = " << split_blocks(max_index).first << "; b = " << split_blocks(max_index).second << std::endl;
    return 0;
}