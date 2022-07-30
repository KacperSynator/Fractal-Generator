#pragma once

#include <memory>

#include "bitmap/bitmap.h"
#include "coloring/coloring.h"
#include "fractal/fractal.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"

class FractalGenerator;

class FractalGeneratorBuilder {
   public:
    FractalGeneratorBuilder() = delete;
    FractalGeneratorBuilder(const int& width, const int& height, const int& max_iterations);
    operator FractalGenerator();
    FractalGeneratorBuilder& MandelbrotFractal();
    FractalGeneratorBuilder& BitmapImage();
    FractalGeneratorBuilder& HistColoring();

   private:
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
    std::unique_ptr<Coloring> coloring_{nullptr};
    int img_width_{0};
    int img_height_{0};
    int max_iterations_{0};
};
