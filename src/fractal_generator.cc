#include "fractal_generator.h"


void FractalGenerator::Generate(const std::string& filename) {
    const int width = image_->Width();
    const int height = image_->Height();
    
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double x_fractal = (x - width / 2) * 2.765 / width - 0.765;
            double y_fractal = (y - height / 2) * 2.22 / height;
            
            int iteration = fractal_->Calculate(x_fractal, y_fractal);
            coloring_->HandleIteration(iteration, x, y);
        }
    }

    const auto color_scales = coloring_->ResultArray();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            u_int8_t color = color_scales[y][x] * 255;
            image_->SetPixel(x, y, 0, 0, color);
        }
    }
    
    image_->Write(filename);
}
