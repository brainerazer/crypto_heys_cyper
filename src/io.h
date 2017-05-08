//
// Created by Bohdan Rybak on 04.05.2017.
//

#ifndef LAB1YAK_IO_H
#define LAB1YAK_IO_H

#include "common.h"
#include <istream>

std::vector<byte_t> input_bytes_from_str(std::istream &i_stream);
std::vector<byte_t> input_bytes_from_bin(std::istream &i_stream);

#endif //LAB1YAK_IO_H
