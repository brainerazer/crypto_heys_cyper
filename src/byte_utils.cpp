//
// Created by Bohdan Rybak on 08.05.2017.
//

#include "byte_utils.h"

namespace
{
    // http://stackoverflow.com/questions/8011700/how-do-I-extract-specific-n-bits-of-a-32-bit-unsigned-integer-in-c
    inline fragm_t extract_fragment(block_t orig16BitWord, uint8_t from, uint8_t to)
    {
        block_t mask = ((1 << (to - from)) - 1) << from;
        return static_cast<fragm_t>((orig16BitWord & mask) >> from);
    }
}


block_t bytes_to_block(byte_t i_byte1, byte_t i_byte2)
{
    return (block_t(i_byte2) << 8) + i_byte1;
}


std::array<fragm_t, 4> split_block(block_t i_block)
{
    std::array<fragm_t, 4> res;
    for(size_t i = 0; i < 4; i++)
        res[i] = extract_fragment(i_block, i * 4, i * 4 + 4);

    return res;
};

uint32_t merge_blocks(block_t a, block_t b)
{
    return (uint32_t(a) << 16) + uint32_t(b);
}

std::pair<uint16_t, uint16_t> split_blocks(uint32_t i_mblock)
{
    uint16_t f = i_mblock >> 16;
    uint16_t s = (uint16_t)i_mblock;

    return std::make_pair(f, s);
}