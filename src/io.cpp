//
// Created by Bohdan Rybak on 04.05.2017.
//

#include "io.h"

namespace
{
    // http://stackoverflow.com/questions/8011700/how-do-I-extract-specific-n-bits-of-a-32-bit-unsigned-integer-in-c
    inline fragm_t extract_fragment(block_t orig16BitWord, uint8_t from, uint8_t to)
    {
        block_t mask = ((1 << (to - from)) - 1) << from;
        return static_cast<fragm_t>((orig16BitWord & mask) >> from);
    }
}

std::vector<byte_t> input_bytes(std::istream& i_stream)
{
    std::vector<byte_t> result;
    std::string tmp;
    i_stream >> tmp;

    if(tmp.size() % 2 == 1)
        tmp = '0' + tmp;

    for(size_t i = 0; i < tmp.size(); i += 2) {
        std::string substr = std::string({tmp[i], tmp[i+1]});
        byte_t b = std::stoi(substr, nullptr, 16);
        result.push_back(b);
    }

    return result;
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