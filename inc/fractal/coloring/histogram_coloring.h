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
    void HandleColorRanges(std::vector<double> color_ranges) override;
    std::vector<std::vector<double> > ResultArray() override;

   private:
    int GetRange(const int& value);

    std::vector<std::vector<int> > iterations_;
    std::vector<int> histogram_;
    std::vector<int> range_histograms_;
    std::vector<double> color_ranges_;

    int data_range{0};
};
