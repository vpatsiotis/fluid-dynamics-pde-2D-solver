#include "boundary.h"
#include <algorithm>

boundary::boundary(const mesh& mesh) {}


void boundary::velocity_boundary(const mesh& mesh, std::vector<std::vector<double>>& u_grid, std::vector<std::vector<double>>& v_grid)
{
    int nx = mesh.get_nx();
    int ny = mesh.get_ny();

     // Upper Wall: u = 1.0, v = 0.0
    for (int j = 0; j < nx; ++j)
    {
        u_grid[ny - 1][j] = 1.0; 
        v_grid[ny - 1][j] = 0.0;
    }

    // Bottom Wall: No-slip (u = 0.0, v = 0.0)
    for (int j = 0; j < nx; ++j)
    {
        u_grid[0][j] = 0.0;
        v_grid[0][j] = 0.0;
    }

    // Left Wall: No-slip (u = 0.0, v = 0.0)
    for (int i = 0; i < ny; ++i)
    {
        u_grid[i][0] = 0.0;
        v_grid[i][0] = 0.0;
    }

    // Right Wall: No-slip (u = 0.0, v = 0.0)
    for (int i = 0; i < ny; ++i)
    {
        u_grid[i][nx - 1] = 0.0;
        v_grid[i][nx - 1] = 0.0;
    }
}

void boundary::pressure_boundary(const mesh& mesh, std::vector<std::vector<double>>& p_grid)
{
    int nx = mesh.get_nx();
    int ny = mesh.get_ny();

    // dp/dn = 0 -> p_n = p_n-1
    // Upper - Bottom Walls
    for (int j = 0; j < nx; ++j)
    {
        p_grid[0][j] = p_grid[1][j];               // Bottom
        p_grid[ny - 1][j] = p_grid[ny - 2][j];     // Top
    }

    // Left - Right Walls
    for (int i = 0; i < ny; ++i)
    {
        p_grid[i][0] = p_grid[i][1];               // Left
        p_grid[i][nx - 1] = p_grid[i][nx - 2];     // Right
    }
}

