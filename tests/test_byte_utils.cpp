//
// Created by Bohdan Rybak on 08.05.2017.
//
#include <catch.hpp>

#include "../src/byte_utils.h"

namespace
{
    // Array to vec, for easy pretty-printing
    template<typename T, unsigned long N>
    std::vector<T> a_to_v(std::array<T, N> i_arr) {
        return std::vector<T>(i_arr.begin(), i_arr.end());
    };
}


TEST_CASE("Bytes to block conversion works fine", "[bytes]") {
    SECTION("Both zero bytes produce zero block") {
        block_t gt = 0x0; // == 0x0000
        block_t block = bytes_to_block(0x00, 0x00);

        REQUIRE(block == gt);
    }

    SECTION("Block converts according to little-endian order") {
        block_t gt = 0x7A1D;
        block_t block = bytes_to_block(0x1D, 0x7A);

        REQUIRE(block == gt);
    }
}

TEST_CASE("Block splits fine", "[bytes]") {
    SECTION("Zero block splits into 4 zero fragments") {
        std::array<fragm_t, 4> gt = {0x0, 0x0, 0x0, 0x0};
        std::array<fragm_t, 4> res = split_block(0x0000);

        REQUIRE(a_to_v(res) == a_to_v(gt));
    }

    SECTION("Block splits according to little-endian order") {
        std::array<fragm_t, 4> gt = {0xD, 0xC, 0xB, 0xA};
        std::array<fragm_t, 4> res = split_block(0xABCD);

        REQUIRE(a_to_v(res) == a_to_v(gt));
    }
}