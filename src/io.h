//
// Created by Bohdan Rybak on 04.05.2017.
//

#ifndef LAB1YAK_IO_H
#define LAB1YAK_IO_H

#include "common.h"

#include <istream>
#include <vector>
#include <array>

std::vector<byte_t> input_bytes_from_str(std::istream &i_stream);
std::vector<byte_t> input_bytes_from_bin(std::istream &i_stream);

block_t bytes_to_block(byte_t i_byte1, byte_t i_byte2);

std::array<fragm_t, 4> split_block(block_t i_block);

#endif //LAB1YAK_IO_H
