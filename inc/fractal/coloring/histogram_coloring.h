#pragma once

#include <memory>
#include <numeric>
#include <vector>
#include <map>

#include "coloring/coloring.h"

class HistogramColoring : public Coloring {
   public:
    HistogramColoring() = delete;
    HistogramColoring(const int& hist_size, const int& img_width, const int& img_height);
    virtual ~HistogramColoring() = default;

    void HandleIteration(const int& iteration, const int& x, const int& y) override;
    void HandleColorRanges(const ColorRanges& color_ranges) override;
    CalculatedColors ResultArray() override;
    void Reset() override;

   private:
    int GetRange(const int& value);
    ColorRange GetColorRange(const int& value);

    std::vector<std::vector<int> > iterations_;
    std::vector<int> histogram_;
    std::vector<int> range_histograms_;
    ColorRanges const* color_ranges_{nullptr};

    int data_range{0};
};
