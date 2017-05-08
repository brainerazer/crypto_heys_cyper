//
// Created by Bohdan Rybak on 04.05.2017.
//

#ifndef LAB1YAK_HEISS_H
#define LAB1YAK_HEISS_H

#include "common.h"

block_t interchange_and_merge(const std::array<fragm_t, 4> &i_arr);

block_t round(block_t i_block, block_t i_key);

std::vector<block_t> split_round_keys(std::vector<byte_t> i_vec);

block_t cipher(block_t i_plaintext, std::vector<block_t> i_round_keys); // N of rounds = len(keys) - 1

#endif //LAB1YAK_HEISS_H
