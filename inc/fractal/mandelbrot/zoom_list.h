#pragma once

#include<vector>
#include<tuple>

#include "mandelbrot/zoom.h"

class ZoomList {
  public:
    ZoomList(const int& width, const int& height) : width_(width), height_(height) {}
    void Add(const Zoom& zoom);
    std::pair<double, double> DoZoom(const int& x, const int& y);

  private:
    double x_center_{0};
    double y_center_{0};
    double scale_{1.0};

    int width_;
    int height_;
    std::vector<Zoom> zooms;
};
