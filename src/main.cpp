#include "utils/system.h"

void print_array (uint8_t data_ptr[], uint8_t data_size)
{
    for(uint8_t i=0u; i<data_size; i++)
        std::cout<< (int32_t)data_ptr[i] << " ";
    std::cout<< std::endl;
}

int main()
{
    uint8_t data_ptr[] = { 0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
                           0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
    uint8_t data_size = 24;
    std::cout<< "before compression:  ";
    print_array(data_ptr, data_size);

    data_size = byte_compress(data_ptr, data_size);
    std::cout<< "after compression:   ";
    print_array(data_ptr, data_size);

    data_size = byte_decompress(data_ptr, data_size);
    std::cout<< "after decompression: ";
    print_array(data_ptr, data_size);
    return 0;
}
