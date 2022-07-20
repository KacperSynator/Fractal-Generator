#pragma once

#include <cmath>
#include <memory>

#include "bitmap/bitmap.h"
#include "coloring/coloring.h"
#include "coloring/histogram_coloring.h"
#include "fractal/fractal.h"
#include "fractal_generator_builder.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"
#include "mandelbrot/zoom_list.h"

class FractalGenerator {
   public:
    friend class FractalGeneratorBuilder;

    static FractalGeneratorBuilder Build() { return {}; }
    void Generate(const std::string& filename);
    void AddZoom(const Zoom& zoom) { zooms_.Add(zoom); }
    void AddZoom(const int& x, const int& y, const double& scale) { zooms_.Add(Zoom{x, y, scale}); }


   private:
    FractalGenerator() = default;
    FractalGenerator(std::unique_ptr<Fractal> fractal, std::unique_ptr<Image> image, std::unique_ptr<Coloring> coloring)
        : fractal_(std::move(fractal)), image_(std::move(image)), coloring_(std::move(coloring)), zooms_(image->Width(), image->Height()) {}

    void CalculateFractal();
    void DrawFractal();

    ZoomList zooms_;
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
    std::unique_ptr<Coloring> coloring_{nullptr};
};
