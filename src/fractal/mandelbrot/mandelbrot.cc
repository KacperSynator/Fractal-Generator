#include "mandelbrot/mandelbrot.h"

int Mandelbrot::Calculate(const double& x, const double& y) {
    return static_cast<double>(GetIterations(x, y));
}

int Mandelbrot::GetIterations(const double& x, const double& y) {
    const static int kMaxMandelbrotAbs{2};

    std::complex<double> z{0}, c{x, y};
    int iterations{0};

    while (iterations < kMaxIterations && std::abs(z) <= kMaxMandelbrotAbs) {
        z = z*z + c;
        iterations++;
    }
    
    return iterations;
}
