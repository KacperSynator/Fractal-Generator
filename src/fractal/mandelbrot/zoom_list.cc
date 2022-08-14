#include "mandelbrot/zoom_list.h"


void ZoomList::Add(const Zoom& zoom) {
    zooms.push_back(zoom);

    x_center_ += (zoom.x - width_ / 2) * scale_;
    y_center_ += (zoom.x - width_ / 2) * scale_;

    scale_ *= zoom.scale;
}

void ZoomList::Pop() {
    if (zooms.empty()) return;
    
    auto last = zooms.back();

    scale_ /= last.scale;

    x_center_ -= (last.x - width_ / 2) * scale_;
    y_center_ -= (last.x - width_ / 2) * scale_;

    zooms.pop_back();
}

void ZoomList::Clear() {
    zooms.clear();
    x_center_ = 0;
    y_center_ = 0;
    scale_ = 1;
}

std::size_t ZoomList::Size() {
    return zooms.size();
}

std::pair<double, double> ZoomList::DoZoom(const int& x, const int& y) {
    double x_fractal = (x - width_ / 2) * scale_ + x_center_;
    double y_fractal = (y - height_ / 2) * scale_ + y_center_;

    return std::make_pair(x_fractal, y_fractal);
}
