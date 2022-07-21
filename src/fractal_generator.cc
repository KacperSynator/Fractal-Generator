#include "fractal_generator.h"

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

void FractalGenerator::ColorScaleFn(const ColorScaleFunc& csf) {
    switch (csf) {
        case ColorScaleFunc::kMultiplication:
            scale_func = [](RGBPixel<uint8_t> pixel, double scale) { return pixel * scale; };
            break;

        case ColorScaleFunc::kPower:
            scale_func = [](RGBPixel<uint8_t> pixel, double scale) { 
                return RGBPixel<uint8_t> {
                    static_cast<uint8_t>(std::pow(pixel.red, scale)),
                    static_cast<uint8_t>(std::pow(pixel.green, scale)),
                    static_cast<uint8_t>(std::pow(pixel.blue, scale))
                };
            };
            break;
        
        default:
            break;
    }
}

std::pair< RGBPixel<uint8_t>, RGBPixel<uint8_t> > FractalGenerator::GetColorRange(const double& scale) {
    int idx = static_cast<int>(scale) / 10;

    return std::make_pair(color_ranges_[idx].second, color_ranges_[idx + 1].second);
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
    const auto color_scales = coloring_->ResultArray();
    for (int x = 0; x < image_->Width(); x++) {
        for (int y = 0; y < image_->Height(); y++) {
            auto color_range = GetColorRange(color_scales[y][x]);
            RGBPixel<uint8_t> color_diff = color_range.second - color_range.first;
            const RGBPixel<uint8_t> color = color_range.first + scale_func(color_diff, color_scales[y][x]);
            image_->SetPixel(x, y, color.red, color.green, color.blue);
        }
    }
}

void FractalGenerator::PassRangesToColoringClass() {
    std::vector<double> ranges(color_ranges_.size());
    std::transform(color_ranges_.begin(), color_ranges_.end(), ranges.begin(), [](auto range){ return range.first; });
    coloring_->HandleColorRanges(std::move(ranges));
}
