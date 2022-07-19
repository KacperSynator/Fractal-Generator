#include "fractal_generator_builder.h"
#include "fractal_generator.h"

    
FractalGeneratorBuilder::operator FractalGenerator() {
    return FractalGenerator(std::move(fractal_), std::move(image_));
}

FractalGeneratorBuilder& FractalGeneratorBuilder::MandelbrotFractal() {
    fractal_ = std::make_unique<Mandelbrot>();
    return *this;
}

FractalGeneratorBuilder& FractalGeneratorBuilder::BitmapImage(const int& width, const int& height) {
    image_ = std::make_unique<Bitmap>(width, height);
    return *this;
}