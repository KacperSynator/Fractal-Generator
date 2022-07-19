#pragma once

#include<memory>

#include "fractal/fractal.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"
#include "bitmap/bitmap.h"

class FractalGenerator;

class FractalGeneratorBuilder {
  public:
    FractalGeneratorBuilder() {}
    operator FractalGenerator();
    FractalGeneratorBuilder& MandelbrotFractal();
    FractalGeneratorBuilder& BitmapImage(const int& width, const int& height);

  private:
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
};
