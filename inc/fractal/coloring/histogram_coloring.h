#pragma once

#include<vector>
#include<numeric>

#include "coloring/coloring.h"


class HistogramColoring : public Coloring {
  public:
    HistogramColoring() = delete;
    HistogramColoring(const int& hist_size, const int& img_width, const int& img_height);
    virtual ~HistogramColoring() = default;

    void HandleIteration(const int& iteration, const int& x, const int& y) override;
    std::vector< std::vector<double> > ResultArray() override;

  private:
    std::vector< std::vector<int> > iterations_;
    std::vector<int> histogram_;

    int total{0};
};