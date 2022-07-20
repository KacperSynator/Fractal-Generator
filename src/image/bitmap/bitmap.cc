#include "bitmap/bitmap.h"

Bitmap::Bitmap(const int& width, const int& height) : width_(width), height_(height) {
    pixels_.resize(height);
    for (auto& row : pixels_)
        row.resize(width);
}

bool Bitmap::Write(const std::string& filename) const {
    auto data_offset = sizeof(BitmapHeader) + sizeof(BitmapInfoHeader);
    auto file_size = data_offset + width_ * height_ * kColorsPerPixel;

    BitmapHeader bitmap_header(file_size, data_offset);
    BitmapInfoHeader bitmap_info_header(width_, -height_);

    std::ofstream ofs(filename + ".bmp", std::ios::binary);

    if (!ofs.is_open()) return false;

    ofs.write(reinterpret_cast<char*>(&bitmap_header), sizeof(BitmapHeader));
    ofs.write(reinterpret_cast<char*>(&bitmap_info_header), sizeof(BitmapInfoHeader));
    for (const auto& row : pixels_)
        for (auto pixel : row)
            ofs.write(reinterpret_cast<char*>(&pixel), kColorsPerPixel);

    return true;
}

bool Bitmap::SetPixel(const int& x, const int& y, const uint8_t& red,
                      const uint8_t& green, const uint8_t& blue) {
    if (y >= height_ || y < 0 || x >= width_ || x < 0) 
        return false;
    
    pixels_[y][x] = Pixel{ blue, green, red };
    return true;
}
