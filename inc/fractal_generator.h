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
    friend class FractalGeneratorBuilder;

    enum ColorScaleFunc { kPower, kMultiplication };

    static FractalGeneratorBuilder Build() { return {}; }
    void Generate(const std::string& filename);
    void AddZoom(const Zoom& zoom) { zooms_.Add(zoom); }
    void AddZoom(const int& x, const int& y, const double& scale) { zooms_.Add(Zoom{x, y, scale}); }
    bool AddColorRange(const double& range_end, const RGBPixel<uint8_t>& color);
    bool AddColorRange(const double& range_end, const uint8_t& red, const uint8_t& green, const uint8_t& blue);
    void ColorScaleFn(const ColorScaleFunc& csf);

   private:
    FractalGenerator() = delete;
    FractalGenerator(std::unique_ptr<Fractal> fractal, std::unique_ptr<Image> image, std::unique_ptr<Coloring> coloring,
                     const ColorScaleFunc& csf = kPower)
        : fractal_(std::move(fractal)),
          image_(std::move(image)),
          coloring_(std::move(coloring)),
          zooms_(image->Width(), image->Height()) {
        ColorScaleFn(csf);
    }

    bool ValidateColorRange(const double& range_end);
    bool ValidateLastColorRange();
    void CalculateFractal();
    void DrawFractal();
    void PassRangesToColoringClass();
    std::pair< RGBPixel<uint8_t>, RGBPixel<uint8_t> > GetColorRange(const double& scale);

    std::vector<std::pair<double, RGBPixel<uint8_t> > > color_ranges_;
    std::function<RGBPixel<uint8_t>(RGBPixel<uint8_t>, double)> scale_func;

    ZoomList zooms_;
    std::unique_ptr<Fractal> fractal_{nullptr};
    std::unique_ptr<Image> image_{nullptr};
    std::unique_ptr<Coloring> coloring_{nullptr};
};
