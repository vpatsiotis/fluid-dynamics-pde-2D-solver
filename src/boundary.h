#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <vector>
#include "mesh.h"

class boundary
{
public:
    boundary(const mesh& mesh);
    void velocity_boundary(const mesh& mesh, std::vector<std::vector<double>>& u_grid, std::vector<std::vector<double>>& v_grid);
    void pressure_boundary(const mesh& mesh, std::vector<std::vector<double>>& p_grid);
};

#endif
