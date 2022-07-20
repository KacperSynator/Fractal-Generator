#pragma once

#include<vector>

class Coloring {
  public:
    virtual void HandleIteration(const int& value, const int& x, const int& y) = 0;
    virtual std::vector< std::vector<double> > ResultArray() = 0;
};