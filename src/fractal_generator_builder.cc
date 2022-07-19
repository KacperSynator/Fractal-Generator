#include "fractal_generator_builder.h"

    
FractalGeneratorBuilder::operator FractalGenerator&() const {
    return std::move(fg_);
}

FractalGeneratorBuilder& FractalGeneratorBuilder::MandelbrotFractal() {
    fg_.fractal_ = std::make_unique<Mandelbrot>();
    return *this;
}

FractalGeneratorBuilder& FractalGeneratorBuilder::BitmapImage(const int& width, const int& height) {
    fg_.image_ = std::make_unique<Bitmap>(width, height);
    return *this;
}