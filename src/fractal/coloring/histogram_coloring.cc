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

void HistogramColoring::HandleColorRanges(const ColorRanges& color_ranges) {
    color_ranges_ = &color_ranges;
    range_histograms_.resize(color_ranges_->size(), 0);
}

RGBPixel<uint8_t> ConvertToPixel(const double& scale, const Coloring::ColorRange& color_range) {
    RGBPixel<int> color_diff{ static_cast<RGBPixel<int>>(color_range.second) -
                              static_cast<RGBPixel<int>>(color_range.first) };

    auto result = static_cast<RGBPixel<int>>(color_range.first) + color_diff * scale;

    return {static_cast<uint8_t>(result.red), static_cast<uint8_t>(result.green), static_cast<uint8_t>(result.blue)};
}

Coloring::CalculatedColors HistogramColoring::ResultArray() {
    Coloring::CalculatedColors result;
    result.reserve(iterations_.size());

    int total = std::accumulate(histogram_.begin(), histogram_.end(), 0);
    for (auto& row : iterations_) {
        std::vector<RGBPixel<uint8_t>> result_row;
        result_row.reserve(row.size());

        for (auto& iteration : row) {
            int total_pixels{0};
            auto range = GetRange(iteration);
            int start = static_cast<int>((*color_ranges_)[range].first * data_range);
            for (int i = start; i < iteration; i++) {
                total_pixels += histogram_[i];
            }

            auto scale = static_cast<double>(total_pixels) / static_cast<double>(range_histograms_[range]);
            result_row.emplace_back(ConvertToPixel(scale, GetColorRange(iteration)));
        }
        result.emplace_back(result_row);
    }
    return std::move(result);
}

int HistogramColoring::GetRange(const int& value) {
    double val = static_cast<double>(value) / data_range;
    for (int i = 1; i < color_ranges_->size(); i++) {
        if (val < (*color_ranges_)[i].first && val >= (*color_ranges_)[i - 1].first) return i - 1;
    }

    throw std::runtime_error("Can't find range (hc)");
}

Coloring::ColorRange HistogramColoring::GetColorRange(const int& value) {
    const auto idx = GetRange(value);

    return std::make_pair((*color_ranges_)[idx].second, (*color_ranges_)[idx + 1].second);
}
