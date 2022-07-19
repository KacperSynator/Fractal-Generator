#pragma once

#include<memory>

#include "fractal/fractal.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"
#include "bitmap/bitmap.h"
#include "fractal_generator_builder.h"

class FractalGenerator {
  public:
    friend class FractalGeneratorBuilder;

    FractalGenerator(const FractalGenerator& other) {};
    static FractalGeneratorBuilder Build() { return {}; }

  private:
    FractalGenerator() {}
    FractalGenerator(std::unique_ptr<Fractal> fractal, std::unique_ptr<Image> image)
            : fractal_(std::move(fractal)), image_(std::move(image)) {}
    
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
};
