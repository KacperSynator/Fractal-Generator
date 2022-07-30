#include "fractal_generator_builder.h"

#include "fractal_generator.h"

FractalGeneratorBuilder::FractalGeneratorBuilder(const int& width, const int& height, const int& max_iterations)
    : max_iterations_(max_iterations), img_width_(width), img_height_(height) {}

FractalGeneratorBuilder::operator FractalGenerator() {
    if (!fractal_) throw std::runtime_error("Fractal not set");
    if (!image_) throw std::runtime_error("Image not set");
    if (!coloring_) throw std::runtime_error("Coloring not set");

    return FractalGenerator(std::move(fractal_), std::move(image_), std::move(coloring_));
}

FractalGeneratorBuilder& FractalGeneratorBuilder::MandelbrotFractal() {
    fractal_ = std::make_unique<Mandelbrot>(max_iterations_);
    return *this;
}

FractalGeneratorBuilder& FractalGeneratorBuilder::BitmapImage() {
    image_ = std::make_unique<Bitmap>(img_width_, img_height_);
    return *this;
}

FractalGeneratorBuilder& FractalGeneratorBuilder::HistColoring() {
    coloring_ = std::make_unique<HistogramColoring>(max_iterations_, img_width_, img_height_);
    return *this;
}
