#pragma once

#include <cstdint>

#pragma pack(2)
struct BitmapHeader {
    char header[2]{'B', 'M'};
    int32_t file_size;
    int32_t reserved{0};
    int32_t data_offset;

    BitmapHeader(const int32_t& file_size, const int32_t& data_offset)
        : file_size(file_size), data_offset(data_offset) {}
};
