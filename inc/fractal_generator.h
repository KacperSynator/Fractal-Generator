#pragma once

#include <cmath>
#include <functional>
#include <memory>

#include "bitmap/bitmap.h"
#include "coloring/coloring.h"
#include "coloring/histogram_coloring.h"
#include "fractal/fractal.h"
#include "fractal_generator_builder.h"
#include "image/image.h"
#include "mandelbrot/mandelbrot.h"
#include "mandelbrot/zoom_list.h"
#include "pixels/rgb_pixel.h"

class FractalGenerator {
   public:
    FractalGenerator() = delete;
    FractalGenerator(const FractalGenerator&) = delete;
    FractalGenerator& operator=(const FractalGenerator&) = delete;
    FractalGenerator(FractalGenerator&&) = default;
    FractalGenerator& operator=(FractalGenerator&&) = default;
    ~FractalGenerator() = default;

    enum ColorScaleFunc { kPower, kMultiplication };

    static FractalGeneratorBuilder Build() { return {}; }
    void Generate(const std::string& filename);
    void AddZoom(const Zoom& zoom) { zooms_.Add(zoom); }
    void AddZoom(const int& x, const int& y, const double& scale) { zooms_.Add(Zoom{x, y, scale}); }
    bool AddColorRange(const double& range_end, const RGBPixel<uint8_t>& color);
    bool AddColorRange(const double& range_end, const uint8_t& red, const uint8_t& green, const uint8_t& blue);

    friend class FractalGeneratorBuilder;

   private:
    using ColorRanges = std::vector< std::pair<double, RGBPixel<uint8_t> > >;
    
    FractalGenerator(std::unique_ptr<Fractal> fractal, std::unique_ptr<Image> image, std::unique_ptr<Coloring> coloring);

    bool ValidateColorRange(const double& range_end);
    bool ValidateLastColorRange();
    void CalculateFractal();
    void DrawFractal();
    void PassRangesToColoringClass();

    ColorRanges color_ranges_;

    ZoomList zooms_;
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
    std::unique_ptr<Coloring> coloring_{nullptr};
};
