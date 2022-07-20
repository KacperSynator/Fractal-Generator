#pragma once

#include <complex>
#include <memory>

#include "fractal/fractal.h"
#include "coloring/coloring.h"
#include "coloring/histogram_coloring.h"

class Mandelbrot : public Fractal {
  public:
    Mandelbrot() = delete;
    explicit Mandelbrot(const int& max_iterations) : kMaxIterations(max_iterations) {}
    virtual ~Mandelbrot() = default;
    int Calculate(const double& x, const double& y) override;

  private:
    const int kMaxIterations;
    int GetIterations(const double& x, const double& y);
    
};
