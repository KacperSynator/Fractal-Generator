#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<fstream>

#include "image/image.h"
#include "bitmap/bitmap_header.h"
#include "bitmap/bitmap_info_header.h"
#include "pixels/rgb_pixel.h"

class Bitmap : public Image {
  public:
    Bitmap(const int& width, const int& height);
    bool Write(const std::string& filename) const override;
    bool SetPixel(const int& x, const int& y, const uint8_t& red,
                  const uint8_t& green, const uint8_t& blue) override;
    int Width() const override { return width_; }
    int Height() const override { return height_; }
    
    virtual ~Bitmap() = default;

  private:
    const int kColorsPerPixel{3};
    int width_{0};
    int height_{0};
    std::vector< std::vector< RGBPixel<uint8_t> > > pixels_;
};
