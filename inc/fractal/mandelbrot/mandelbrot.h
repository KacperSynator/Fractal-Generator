#pragma once

#include <complex>
#include <memory>

#include "fractal/fractal.h"
#include "coloring/coloring.h"

class Mandelbrot : public Fractal {
  public:
    Mandelbrot() = default;
    virtual ~Mandelbrot() = default;
    double Calculate(const double& x, const double& y) override;

  private:
    int GetIterations(const double& x, const double& y);

    static const int kMaxIterations{1000};
    std::unique_ptr<Coloring> coloring_;
};
