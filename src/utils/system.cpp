#include "system.h"

// assuming maximum size of the array will be 256
// if not, we can just change the datatype and a little change in the codebase
uint8_t byte_compress(uint8_t data_ptr[], uint8_t data_size)
{
    if(data_size == 0u) // if the array is empty, nothing to compress
        return 0u;
    auto start_time = std::chrono::steady_clock::now();

    uint8_t prev_val = data_ptr[0], prev_val_cnt = 1u;
    uint8_t cur_read_ptr = 1u, cur_write_ptr = 0u;

    while(cur_read_ptr <= data_size)
    {
        uint8_t cur_val = cur_read_ptr < data_size ? data_ptr[cur_read_ptr] : 0xFF; // cur_val = 0xFF, to include the last element of the array
        if(cur_val == prev_val)
            prev_val_cnt++;
        else
        {
            if(prev_val_cnt == 1) // no special action needed, just insert the value
                data_ptr[cur_write_ptr++] = prev_val;
            else
            {
                // assuming repeated sequence will be less than 128, we can store the repeat count in the first 7 bit
                // set the 8th bit of the counter to 1, indicating it is a repeat count index
                prev_val_cnt |= (uint8_t)(1u << 7);

                // now insert the duplicate count at the current location of the array
                data_ptr[cur_write_ptr++] = prev_val_cnt;

                // insert the number in the next location
                data_ptr[cur_write_ptr++] = prev_val;
            }
            // update prev_val and prev_val_cnt
            prev_val = cur_val;
            prev_val_cnt = 1u;
        }
        cur_read_ptr++;
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout<<"data compression took: " << elapsed_time.count() << "ns" << std::endl;
    return cur_write_ptr;
}

uint8_t byte_decompress(uint8_t data_ptr[], uint8_t data_size)
{
    if(data_size == 0u) // if the array is empty, nothing to decompress
        return 0u;
    auto start_time = std::chrono::steady_clock::now();

    // first count the total number of elements
    uint8_t total_data_size = 0u;
    for(auto i=0u; i<data_size; i++)
    {
        if(data_ptr[i] >> 7 == 1u) // this number is duplicate
            total_data_size += data_ptr[i++] & ~((uint8_t)1u << 7); // (i++), because next index is the number itself, so ignore
        else
            total_data_size++; // this number is single in the series
    }

    // we will decompress the array from the end, so that we don't loss information
    uint8_t cur_read_ptr = data_size - 1u, cur_write_ptr = total_data_size - 1u;
    do
    {
        auto cur_val = data_ptr[cur_read_ptr];
        uint8_t cur_val_cnt = 1u;
        // let's check if this number has repition
        if(cur_read_ptr > 0 && data_ptr[cur_read_ptr-1] >> 7 == 1u)
            cur_val_cnt = data_ptr[--cur_read_ptr] ^ (uint8_t)(1u << 7);
        // now add the bytes in the array
        for(uint8_t i=0u; i<cur_val_cnt; i++)
            data_ptr[cur_write_ptr--] = cur_val;
    } while(cur_read_ptr--);

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout<<"data decompression took: " << elapsed_time.count() << "ns" << std::endl;
    return total_data_size;
}
