#include "fractal_generator.h"

FractalGenerator::FractalGenerator(std::unique_ptr<Fractal> fractal, std::unique_ptr<Image> image,
                                   std::unique_ptr<Coloring> coloring)
    : fractal_(std::move(fractal)),
      image_(std::move(image)),
      coloring_(std::move(coloring)),
      zooms_(image->Width(), image->Height()) {}

void FractalGenerator::Generate(const std::string& filename) {
    if (!ValidateLastColorRange()) return;
    PassRangesToColoringClass();
    CalculateFractal();
    DrawFractal();
    image_->Write(filename);
}

bool FractalGenerator::AddColorRange(const double& range_end, const RGBPixel<uint8_t>& color) {
    if (!ValidateColorRange(range_end)) return false;

    color_ranges_.emplace_back(std::make_pair(range_end, color));

    return true;
}

bool FractalGenerator::AddColorRange(const double& range_end, const uint8_t& red, const uint8_t& green,
                                     const uint8_t& blue) {
    return AddColorRange(range_end, RGBPixel<uint8_t>{red, green, blue});
}


void FractalGenerator::PopColorRange() {
    if (!color_ranges_.empty()) {
        color_ranges_.pop_back();
    }
}

bool FractalGenerator::ValidateLastColorRange() {
    if (color_ranges_.back().first != 1.0) {
        std::cout << "Last color range is not equals to 1.0\n";
        return false;
    }

    return true;
}

bool FractalGenerator::ValidateColorRange(const double& range_end) {
    if (range_end > 1.0 || range_end < 0.0) {
        std::cout << "Color range must be from [0, 1] given: " << range_end << std::endl;
        return false;
    }

    if (color_ranges_.empty() && range_end != 0.0) {
        std::cout << "First color range must be 0.0\n";
        return false;
    }

    if (!color_ranges_.empty() && color_ranges_.back().first >= range_end) {
        std::cout << "New color range " << range_end << " is less than last value " << color_ranges_.back().first
                  << std::endl;
        return false;
    }

    return true;
}

void FractalGenerator::CalculateFractal() {
    for (int x = 0; x < image_->Width(); x++) {
        for (int y = 0; y < image_->Height(); y++) {
            auto coords = zooms_.DoZoom(x, y);
            int iteration = fractal_->Calculate(coords.first, coords.second);
            coloring_->HandleIteration(iteration, x, y);
        }
    }
}

void FractalGenerator::DrawFractal() {
    const auto pixels = coloring_->ResultArray();
    for (int x = 0; x < image_->Width(); x++) {
        for (int y = 0; y < image_->Height(); y++) {
            image_->SetPixel(x, y, pixels[y][x]);
        }
    }
}

void FractalGenerator::PassRangesToColoringClass() { coloring_->HandleColorRanges(color_ranges_); }
