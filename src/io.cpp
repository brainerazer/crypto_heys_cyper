//
// Created by Bohdan Rybak on 04.05.2017.
//

#include "io.h"

#include <iterator>

std::vector<byte_t> input_bytes_from_str(std::istream &i_stream)
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

std::vector<byte_t> input_bytes_from_bin(std::istream &i_stream)
{
    std::vector<byte_t> result((std::istreambuf_iterator<char>(i_stream)), std::istreambuf_iterator<char>());
    return result;
}


