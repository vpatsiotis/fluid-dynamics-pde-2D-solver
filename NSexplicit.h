#pragma once
#include <vector>
#include "mesh.h"
#include "boundary.h"
#include "visual.h"

class NSexplicit
{
private:
    double m, dt, nt, rho;
    int write_interval;
    int nx, ny; 

    std::vector<std::vector<double>> u;
    std::vector<std::vector<double>> un;
    std::vector<std::vector<double>> v;
    std::vector<std::vector<double>> vn;
    std::vector<std::vector<double>> p;
    std::vector<std::vector<double>> pn;

    const mesh& mesh_ref; 
    boundary& bc_ref;

public:
    NSexplicit(const mesh& mesh, boundary& bc, double dt, double visc, double rho, double nt, int write_interval);

    void calc();
};