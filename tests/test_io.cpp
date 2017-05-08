//
// Created by Bohdan Rybak on 04.05.2017.
//

#include <catch.hpp>

#include "../src/io.h"

namespace
{
    // Array to vec, for easy pretty-printing
    template<typename T, unsigned long N>
    std::vector<T> a_to_v(std::array<T, N> i_arr) {
        return std::vector<T>(i_arr.begin(), i_arr.end());
    };
}

TEST_CASE("Inputting bytes works fine", "[input]") {
    SECTION("No input is empty vector") {
        std::istringstream iss("");
        auto vec = input_bytes(iss);

        REQUIRE(vec.size() == 0);
    }

    SECTION("Input of 16 hex symbols is vector of 8 bytes") {
        std::istringstream iss("001122334455AAFF");
        auto vec = input_bytes(iss);

        REQUIRE(vec.size() == 8);
    }

    SECTION("Input of 16 hex symbols is transformed to the correct vector") {
        std::istringstream iss("001122334455AAFF");
        std::vector<byte_t> gt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xFF};
        auto vec = input_bytes(iss);

        REQUIRE(vec == gt);
    }

    SECTION("Input of 15 hex symbols is transformed to the correct vector") {
        std::istringstream iss("01122334455AAFF");
        std::vector<byte_t> gt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xFF};
        auto vec = input_bytes(iss);

        REQUIRE(vec == gt);
    }
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