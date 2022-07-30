#pragma once

#include <cstdint>
#include <string>

#include "pixels/rgb_pixel.h"

class Image {
   public:
    virtual bool Write(const std::string& filename) const = 0;
    virtual bool SetPixel(const int& x, const int& y, const uint8_t& red, const uint8_t& green,
                          const uint8_t& blue) = 0;
    virtual bool SetPixel(const int& x, const int& y, const RGBPixel<uint8_t>& pixel) = 0;
    virtual int Width() const = 0;
    virtual int Height() const = 0;
};