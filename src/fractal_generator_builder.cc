#include "fractal_generator_builder.h"

#include "fractal_generator.h"

FractalGeneratorBuilder::operator FractalGenerator() {
    if (!fractal_) throw std::runtime_error("Fractal not set");
    if (!image_) throw std::runtime_error("Image not set");
    if (!coloring_) throw std::runtime_error("Coloring not set");

    return FractalGenerator(std::move(fractal_), std::move(image_), std::move(coloring_));
}

FractalGeneratorBuilder& FractalGeneratorBuilder::MandelbrotFractal(const int& max_iterations) {
    fractal_ = std::make_unique<Mandelbrot>(max_iterations);
    return *this;
}

FractalGeneratorBuilder& FractalGeneratorBuilder::BitmapImage(const int& width, const int& height) {
    image_ = std::make_unique<Bitmap>(width, height);
    return *this;
}

FractalGeneratorBuilder& FractalGeneratorBuilder::HistColoring(const int& hist_size, const int& img_width,
                                                               const int& img_height) {
    coloring_ = std::make_unique<HistogramColoring>(hist_size, img_width, img_height);
    return *this;
}
