//
// Created by Bohdan Rybak on 04.05.2017.
//

#ifndef LAB1YAK_HEIS_H
#define LAB1YAK_HEIS_H

#include "common.h"

block_t interchange_and_merge(const std::array<fragm_t, 4> &i_arr);

block_t round(block_t i_block, block_t i_key);

std::vector<block_t> split_round_keys(const std::vector<byte_t>& i_vec);

// Just apply len(i_round_keys) rounds
block_t cipher_rounds(block_t i_plaintext, const std::vector<block_t>& i_round_keys);

// Apply len(i_round_keys - 1) rounds, then perform final round with the last key in vector
block_t cipher(block_t i_plaintext, const std::vector<block_t>& i_round_keys);

#endif //LAB1YAK_HEIS_H
