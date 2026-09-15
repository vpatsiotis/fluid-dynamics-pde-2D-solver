#pragma once
#include <vector>
#include "mesh.h"

class conditions
{
private:

    double T_West, T_East, T_South, T_North;
    std::vector<std::vector<double>> T;

public:
    conditions(const mesh& mesh, double _T_West, double _T_East, double _T_South, double _T_North);
    void boundary(const mesh& mesh);

    const std::vector<std::vector<double>>& get_T() const { return T; }
};

