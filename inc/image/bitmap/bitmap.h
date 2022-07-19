#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<fstream>

#include "image/image.h"
#include "bitmap/bitmap_header.h"
#include "bitmap/bitmap_info_header.h"

class Bitmap : public Image {
  public:
    Bitmap(const int& width, const int& height);
    bool Write(const std::string& filename) const override;
    bool SetPixel(const int& x, const int& y, const uint8_t& red,
                  const uint8_t& green, const uint8_t& blue) override;
    virtual ~Bitmap() = default;

    struct Pixel { uint8_t blue{0}, green{0}, red{0}; };

  private:
    const int kColorsPerPixel{3};
    int width_{0};
    int height_{0};
    std::vector< std::vector<Pixel> > pixels_;
};
