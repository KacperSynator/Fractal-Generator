#include "fractal_generator.h"


void FractalGenerator::Generate(const std::string& filename) {
    CalculateFractal();
    DrawFractal();
    image_->Write(filename);
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
            u_int8_t color = std::pow(255, color_scales[y][x]) ;
            image_->SetPixel(x, y, 0, color, 0);
        }
    }
}
