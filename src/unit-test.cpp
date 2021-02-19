#include "utils/system.h"

#define CATCH_CONFIG_MAIN       // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"     // This includes the catch header, which defines the entire library

SCENARIO( "testing byte_compress method", "[compressor]" ) {
    GIVEN( "an array of bytes and array size" ) {
        WHEN( "there is only 1 byte" ) {
            THEN( "the output will contain the same byte" ) {
                uint8_t data_ptr[] = {0x3A};
                uint8_t data_size = 1u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_compress(data_ptr, data_size)} == std::vector<uint8_t>{0x3A}); // converting to vector for easy comparison, could overload == operator too
            }
        }

        WHEN( "there are 2 different bytes" ) {
            THEN( "the output will contain the same size and bytes" ) {
                uint8_t data_ptr[] = {0x3A, 0x7F};
                uint8_t data_size = 2u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_compress(data_ptr, data_size)} == std::vector<uint8_t>{0x3A, 0x7F});
            }
        }

        WHEN( "there are 2 same bytes" ) {
            THEN( "the output will be same size but different bytes (1st count, 2nd the byte)" ) {
                uint8_t data_ptr[] = {0x7F, 0x7F};
                uint8_t data_size = 2u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_compress(data_ptr, data_size)} == std::vector<uint8_t>{0x82, 0x7F}); // 0x82 = 1000 0010, 8th bit denotes it's a count index
            }
        }

        WHEN( "there are 6 same bytes" ) {
            THEN( "the output size will be 2" ) {
                uint8_t data_ptr[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F};
                uint8_t data_size = 6u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_compress(data_ptr, data_size)} == std::vector<uint8_t>{0x86, 0x7F});
            }
        }

        WHEN( "there are 3 same bytes + 4 same bytes" ) {
            THEN( "the output size will be 4" ) {
                uint8_t data_ptr[] = {0x5A, 0X5A, 0x5A, 0x7F, 0x7F, 0x7F, 0x7F};
                uint8_t data_size = 7u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_compress(data_ptr, data_size)} == std::vector<uint8_t>{0x83, 0x5A, 0x84, 0x7F});
            }
        }
    }
}

SCENARIO( "testing byte_decompress method", "[compressor]" ) {
    GIVEN( "an array of compressed bytes and array size" ) {
        WHEN( "there is only 1 byte" ) {
            THEN( "it will return the same byte" ) {
                uint8_t data_ptr[] = {0x3A};
                uint8_t data_size = 1u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_decompress(data_ptr, byte_compress(data_ptr, data_size))} == std::vector<uint8_t>{0x3A}); // converting to vector for easy comparison, could overload == operator too
            }
        }

        WHEN( "there are 2 different bytes" ) {
            THEN( "it will return the same size and bytes" ) {
                uint8_t data_ptr[] = {0x3A, 0x7F};
                uint8_t data_size = 2u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_decompress(data_ptr, byte_compress(data_ptr, data_size))} == std::vector<uint8_t>{0x3A, 0x7F});
            }
        }

        WHEN( "there are 2 same bytes" ) {
            THEN( "it will decompress the array into two similar bytes" ) {
                uint8_t data_ptr[] = {0x7F, 0x7F};
                uint8_t data_size = 2u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_decompress(data_ptr, byte_compress(data_ptr, data_size))} == std::vector<uint8_t>{0x7F, 0x7F});
            }
        }

        WHEN( "there are 6 same bytes" ) {
            THEN( "it will decompress the array into 6 similar bytes" ) {
                uint8_t data_ptr[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F};
                uint8_t data_size = 6u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_decompress(data_ptr, byte_compress(data_ptr, data_size))} == std::vector<uint8_t>{0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F});
            }
        }

        WHEN( "there are 3 same bytes + 4 same bytes" ) {
            THEN( "it will decompress the array to it's original bytes" ) {
                uint8_t data_ptr[] = {0x5A, 0X5A, 0x5A, 0x7F, 0x7F, 0x7F, 0x7F};
                uint8_t data_size = 7u;
                REQUIRE(std::vector<uint8_t>{data_ptr, data_ptr + byte_decompress(data_ptr, byte_compress(data_ptr, data_size))} == std::vector<uint8_t>{0x5A, 0X5A, 0x5A, 0x7F, 0x7F, 0x7F, 0x7F});
            }
        }
    }
}
