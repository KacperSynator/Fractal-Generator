#pragma once

#include<memory>

#include "fractal/fractal.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"
#include "bitmap/bitmap.h"

class FractalGeneratorBuilder;

class FractalGenerator {
  public:
    friend class FractalGeneratorBuilder;

    FractalGenerator(const FractalGenerator& other) {};
    static FractalGeneratorBuilder& Build();

  private:
    FractalGenerator() {}
    
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
};
