#include "conditions.h"
#include <algorithm>

conditions::conditions(const mesh& mesh, double _T_West, double _T_East, double _T_South, double _T_North)
    :T_West(_T_West), T_East(_T_East), T_South(_T_South), T_North(_T_North)
{
    T.assign(mesh.get_ny(), std::vector<double>(mesh.get_nx(), 0.0));

}

void conditions::boundary(const mesh& mesh)
{
    int nx = mesh.get_nx();
    int ny = mesh.get_ny();

    for (int j = 0; j < nx - 1; ++j)
    {
        T[0][j] = T_South;
        T[ny-1][j] = T_North;  
    }

    for (int i = 0; i < ny - 1; ++i)
    {
        T[i][0] = T_West;
        T[i][nx-1] = T_East; 
    }

    if (T_West > T_South)
    {
        T[0][0] = T_West;
    }
    else
    {
        T[0][0] = T_South;
    }

    if (T_East > T_South)
    {
        T[0][nx-1] = T_East;
    }
    else
    {
        T[0][nx-1] = T_South;
    }

    if (T_West > T_North)
    {
        T[ny-1][0] = T_West;
    }
    else
    {
        T[ny-1][0] = T_North;
    }

        if (T_East > T_North)
    {
        T[ny-1][nx-1] = T_East;
    }
    else
    {
        T[ny-1][nx-1] = T_North;
    }
}