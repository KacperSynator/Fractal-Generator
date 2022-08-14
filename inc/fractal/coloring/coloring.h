#pragma once

#include <vector>

#include "pixels/rgb_pixel.h"

class Coloring {
  public:
    using ColorRange = std::pair< RGBPixel<uint8_t>, RGBPixel<uint8_t> >;
    using ColorRanges = std::vector< std::pair<double, RGBPixel<uint8_t> > >;
    using CalculatedColors = std::vector< std::vector<RGBPixel<uint8_t> > >;

    virtual void HandleIteration(const int& value, const int& x, const int& y) = 0;
    virtual void HandleColorRanges(const ColorRanges& color_ranges) = 0;
    virtual CalculatedColors ResultArray() = 0;
    virtual void Reset() = 0;
};
