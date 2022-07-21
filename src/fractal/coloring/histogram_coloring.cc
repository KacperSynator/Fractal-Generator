#include "coloring/histogram_coloring.h"
#include <iostream>


HistogramColoring::HistogramColoring(const int& hist_size, const int& img_width, const int& img_height)
    : data_range(hist_size) {
    histogram_.resize(hist_size, 0);

    iterations_.resize(img_height);
    for (auto& row : iterations_) row.resize(img_width);
}

void HistogramColoring::HandleIteration(const int& value, const int& x, const int& y) {
    if (value >= histogram_.size() || value < 0) return;
    if (y < 0 || x < 0 || y >= iterations_.size() || x >= iterations_[0].size()) return;

    histogram_[value]++;
    range_histograms_[GetRange(value)]++;
    iterations_[y][x] = value;
}

void HistogramColoring::HandleColorRanges(std::vector<double> color_ranges) {
    color_ranges_ = std::move(color_ranges);
    range_histograms_.resize(color_ranges_.size(), 0);
}

std::vector<std::vector<double> > HistogramColoring::ResultArray() {
    std::vector< std::vector<double> > result;
    result.reserve(iterations_.size());

    int total = std::accumulate(histogram_.begin(), histogram_.end(), 0);
    for (auto& row : iterations_) {
        std::vector<double> result_row;
        result_row.reserve(row.size());

        for (auto& iteration : row) {
            int total_pixels{0};
            auto range = GetRange(iteration);
            int start = static_cast<int>(color_ranges_[range] * data_range);
            for (int i = start; i < iteration; i++) {
                total_pixels += histogram_[i];
            }
            // std::cout << color_ranges_[range] << " " << range_histograms_[range] << " " << iteration << " " << total_pixels << "\n";
            result_row.emplace_back(static_cast<double>(total_pixels) / static_cast<double>(range_histograms_[range]) + range * 10);
        }
        result.emplace_back(result_row);
    }
    return std::move(result);
}

int HistogramColoring::GetRange(const int& value) {
    double val = static_cast<double>(value) / data_range;
    for (int i = 1; i < color_ranges_.size(); i++) {
        if (val < color_ranges_[i] && val >= color_ranges_[i - 1])
            return i - 1;
    }
    std::cout << value << "\n" ;
    throw std::runtime_error("Can't find range (hc)");
}
