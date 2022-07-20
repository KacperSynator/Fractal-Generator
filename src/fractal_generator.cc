#include "fractal_generator.h"


void FractalGenerator::Generate(const std::string& filename) {
    const int width = image_->Width();
    const int height = image_->Height();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double x_fractal = (x - width / 2) * 2.765 / width - 0.765;
            double y_fractal = (y - height / 2) * 2.22 / height;

            double scale_value = fractal_->Calculate(x_fractal, y_fractal);

            uint8_t color = static_cast<uint8_t>(255.0 * scale_value);

            color *= color * 2;

            image_->SetPixel(x, y, 0, 0, color);
        }
    }

    image_->Write(filename);
}
