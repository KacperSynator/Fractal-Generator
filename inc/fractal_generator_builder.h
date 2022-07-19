#pragma once

#include<memory>

#include "fractal_generator.h"
#include "fractal/fractal.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"
#include "bitmap/bitmap.h"


class FractalGeneratorBuilder {
  public:
    FractalGeneratorBuilder(FractalGenerator& fg) : fg_(fg) {}
    operator FractalGenerator&() const;
    FractalGeneratorBuilder& MandelbrotFractal();
    FractalGeneratorBuilder& BitmapImage(const int& width, const int& height);

  private:
    FractalGenerator& fg_;
};
