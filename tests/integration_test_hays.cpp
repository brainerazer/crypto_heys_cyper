//
// Created by Bohdan Rybak on 08.05.2017.
//

#include <catch.hpp>
#include <fstream>
#include <iostream>

#include "../src/io.h"
#include "../src/hays.h"
#include "../src/byte_utils.h"


TEST_CASE("Hays encription integrated corresponds to the output of GT application", "[integration]") {
    SECTION("First hays integration testcase") {
        std::ifstream key_stream("tests/data/key1.bin", std::ios::binary);
        std::ifstream plaintext_stream("tests/data/plaintext1.txt", std::ios::binary); // 2 bytes
        std::ifstream gt_ciphertext_stream("tests/data/ciphertext1.bin", std::ios::binary); // 2 bytes

        auto key_bytes = input_bytes_from_bin(key_stream);
        auto pt_bytes = input_bytes_from_bin(plaintext_stream);
        auto gt_ct_bytes = input_bytes_from_bin(gt_ciphertext_stream);

        block_t pt_block = bytes_to_block(pt_bytes[0], pt_bytes[1]);
        block_t gt_ct_block = bytes_to_block(gt_ct_bytes[0], gt_ct_bytes[1]);

        auto round_keys = split_round_keys(key_bytes);

        block_t ciphertext_block = cipher(pt_block, round_keys);

        REQUIRE(ciphertext_block == gt_ct_block);
    }
}
