#include "coloring/histogram_coloring.h"


HistogramColoring::HistogramColoring(const int& hist_size, const int& img_width, const int& img_height) {
    histogram_.resize(hist_size, 0);

    iterations_.resize(img_height);
    for (auto& row : iterations_)
        row.resize(img_width);
}

void HistogramColoring::HandleIteration(const int& value, const int& x, const int& y) {
    if (value >= histogram_.size() || value < 0) return;
    if (y < 0 || x < 0 || y >= iterations_.size() || x >= iterations_[0].size()) return;
    
    histogram_[value]++;
    iterations_[y][x] = value;
}

std::vector< std::vector<double> > HistogramColoring::ResultArray() {
    std::vector< std::vector<double> > result;
    result.reserve(iterations_.size());

    int total = std::accumulate(histogram_.begin(), histogram_.end(), 0);
    for (auto& row : iterations_) {

        std::vector<double> result_row;
        result_row.reserve(row.size());

        for (auto& iteration : row) {
            double hue{0.0};
            for (int i = 0; i < iteration; i++) {
                hue += static_cast<double>(histogram_[i]) / static_cast<double>(total);
            }
            result_row.emplace_back(hue);
        }
        result.emplace_back(result_row);
    }
    return std::move(result);
}
