#pragma once

#include<string>
#include<cstdint>

class Image {
  public:
    virtual bool Write(const std::string& filename) const = 0;
    virtual bool SetPixel(const int& x, const int& y, const uint8_t& red,
                          const uint8_t& green, const uint8_t& blue) = 0;
};