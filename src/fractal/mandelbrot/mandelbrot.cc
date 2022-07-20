#include "mandelbrot/mandelbrot.h"

double Mandelbrot::Calculate(const double& x, const double& y) {
    return static_cast<double>(GetIterations(x, y)) / static_cast<double>(kMaxIterations);
}

int Mandelbrot::GetIterations(const double& x, const double& y) {
    const static int kMaxMandelbrotAbs{2};

    std::complex<double> z{0}, c{x, y};
    int iterations{0};

    for (; iterations < kMaxIterations && std::abs(z) <= kMaxMandelbrotAbs; iterations++) {
        z = z*z + c;
    }
    
    return iterations;
}
