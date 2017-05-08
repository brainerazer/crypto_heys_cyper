//
// Created by Bohdan Rybak on 08.05.2017.
//

#include <catch.hpp>

#include "../src/hays.h"

TEST_CASE("Interchange and merge works fine", "[hays]") {
    SECTION("Interchanges and merges does its job") {
        // random
        std::array<fragm_t, 4> chunks_array = {0b1110, 0b1101, 0b0011, 0b0101};
        block_t gt = 0b0011101101011110;
        block_t result = interchange_and_merge(chunks_array);

        REQUIRE(result == gt);
    }
}

TEST_CASE("Round keys splitting works fine", "[hays]") {
    SECTION("Round keys splitting returns 4-block vector from 8-byte vector") {
        auto res = split_round_keys({0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0, 0x01, 0x12});

        REQUIRE(res.size() == 4);
    }

    SECTION("Round keys splitting splits well-formed array into proper keys") {
        std::vector<block_t> gt = {0xBCAB, 0xDECD, 0xF0EF, 0x1201};
        auto res = split_round_keys({0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0, 0x01, 0x12});

        REQUIRE(res == gt);
    }
}

