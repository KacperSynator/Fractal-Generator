#pragma once

#include "fractal/fractal.h"

class Mandelbrot : public Fractal {
  public:
    Mandelbrot() = default;
    virtual ~Mandelbrot() = default;
    void foo() override {}

  private:
    const int kMaxIterations{1000};
};
