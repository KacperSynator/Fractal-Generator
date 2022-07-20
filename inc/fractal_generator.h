#pragma once

#include <memory>

#include "bitmap/bitmap.h"
#include "fractal/fractal.h"
#include "fractal_generator_builder.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"

class FractalGenerator {
   public:
    friend class FractalGeneratorBuilder;

    static FractalGeneratorBuilder Build() { return {}; }
    void Generate(const std::string& filename);

   private:
    FractalGenerator() = default;
    FractalGenerator(std::unique_ptr<Fractal> fractal, std::unique_ptr<Image> image, std::unique_ptr<Coloring> coloring)
        : fractal_(std::move(fractal)), image_(std::move(image)), coloring_(std::move(coloring)) {}

    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
    std::unique_ptr<Coloring> coloring_{nullptr};
};
