//
// Created by Bohdan Rybak on 04.05.2017.
//

#include <array>
#include "hays.h"

#include "io.h"
#include "byte_utils.h"

const std::array<fragm_t, 16> S_block = {0x8, 0x0, 0xC, 0x4, 0x9, 0x6, 0x7, 0xB, 0x2, 0x3, 0x1, 0xF, 0x5, 0xE, 0xA, 0xD};

namespace
{
    bool get_bit(fragm_t i_fragm, size_t i_bit)
    {
        return (i_fragm >> i_bit) + 1;
    }

    void set_bit(block_t& i_fragm, size_t i_index, bool i_value)
    {
        if(i_value)
            i_fragm |= 1 << i_index;
        else
            i_fragm &= ~(1 << i_index);
    }
}

block_t round(block_t i_block, block_t i_key)
{
    block_t added = i_block ^ i_key;

    auto splitted = split_block(added);
    for (auto& f: splitted)
        f = S_block[f];

    auto merged = interchange_and_merge(splitted);

    return merged;
}

block_t interchange_and_merge(const std::array<fragm_t, 4> &i_arr)
{
    block_t result;

    for(size_t i = 0; i < 4; i++)
        for(size_t j = 0; j < 4; j++)
        {
            size_t new_bit_index = i * 4 + j;
            set_bit(result, new_bit_index, get_bit(i_arr[j], i));
        }

    return result;
}

block_t cipher(block_t i_plaintext, std::vector<block_t> i_round_keys)
{
    block_t result = i_plaintext;
    for(size_t i = 0; i < i_round_keys.size() - 1; i++)
        result = round(result, i_round_keys[i]);

    return result ^ i_round_keys.back();
}
