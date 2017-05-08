//
// Created by Bohdan Rybak on 04.05.2017.
//

#include <catch.hpp>

#include "../src/io.h"


TEST_CASE("Inputting bytes from string works fine", "[input]") {
    SECTION("No input is empty vector") {
        std::istringstream iss("");
        auto vec = input_bytes_from_str(iss);

        REQUIRE(vec.size() == 0);
    }

    SECTION("Input of 16 hex symbols is vector of 8 bytes") {
        std::istringstream iss("001122334455AAFF");
        auto vec = input_bytes_from_str(iss);

        REQUIRE(vec.size() == 8);
    }

    SECTION("Input of 16 hex symbols is transformed to the correct vector") {
        std::istringstream iss("001122334455AAFF");
        std::vector<byte_t> gt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xFF};
        auto vec = input_bytes_from_str(iss);

        REQUIRE(vec == gt);
    }

    SECTION("Input of 15 hex symbols is transformed to the correct vector") {
        std::istringstream iss("01122334455AAFF");
        std::vector<byte_t> gt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xFF};
        auto vec = input_bytes_from_str(iss);

        REQUIRE(vec == gt);
    }
}

TEST_CASE("Inputting bytes from binary works fine", "[input]") {
    SECTION("No input is empty vector") {
        std::istringstream iss("");
        auto vec = input_bytes_from_bin(iss);

        REQUIRE(vec.size() == 0);
    }

    SECTION("Input of 8 bytes is a vector of 8 bytes") {
        std::vector<byte_t> bytes = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xFF};
        std::istringstream iss(std::string(std::begin(bytes), std::end(bytes)));

        auto vec = input_bytes_from_bin(iss);

        REQUIRE(vec.size() == 8);
    }

    SECTION("Input of 8 bytes is transformed to the correct vector") {
        std::vector<byte_t> gt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA, 0xFF};
        std::istringstream iss(std::string(std::begin(gt), std::end(gt)));
        auto vec = input_bytes_from_bin(iss);

        REQUIRE(vec == gt);
    }

    SECTION("Input of 7 bytes is transformed to the correct vector") {
        std::vector<byte_t> gt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0xAA};
        std::istringstream iss(std::string(std::begin(gt), std::end(gt)));
        auto vec = input_bytes_from_bin(iss);

        REQUIRE(vec == gt);
    }
}