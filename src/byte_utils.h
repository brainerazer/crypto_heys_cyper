//
// Created by Bohdan Rybak on 08.05.2017.
//

#ifndef LAB1YAK_BYTE_UTILS_H
#define LAB1YAK_BYTE_UTILS_H

#include "common.h"

block_t bytes_to_block(byte_t i_byte1, byte_t i_byte2);
std::array<fragm_t, 4> split_block(block_t i_block);

uint32_t merge_blocks(block_t a, block_t b);
std::pair<uint16_t, uint16_t> split_blocks(uint32_t i_mblock);


#endif //LAB1YAK_BYTE_UTILS_H
