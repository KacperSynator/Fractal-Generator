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
    FractalGeneratorBuilder() {}
    operator FractalGenerator();
    FractalGeneratorBuilder& MandelbrotFractal(const int& max_iterations);
    FractalGeneratorBuilder& BitmapImage(const int& width, const int& height);
    FractalGeneratorBuilder& HistColoring(const int& hist_size, const int& img_width, const int& img_height);

   private:
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
    std::unique_ptr<Coloring> coloring_{nullptr};
};
