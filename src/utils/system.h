#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

uint8_t byte_compress(uint8_t data_ptr[], uint8_t data_size);
uint8_t byte_decompress(uint8_t data_ptr[], uint8_t data_size);

#endif // SYSTEM_H
