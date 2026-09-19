#include "visual.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

visual::visual(const mesh& mesh)
    :m_mesh(mesh)
{
}

double toBigEndian(double val) {
    char* bytes = reinterpret_cast<char*>(&val);
    std::reverse(bytes, bytes + sizeof(double));
    return val;
}

void visual::vtkFile(int current_nt, const std::vector<std::vector<double>>& u, const std::vector<std::vector<double>>& v, const std::vector<std::vector<double>>& p)
{
    std::string filename = "cavity_" + std::to_string(current_nt) + ".vtk";
    std::ofstream vtkFile(filename, std::ios::out | std::ios::binary);
    
    int nx = m_mesh.get_nx();
    int ny = m_mesh.get_ny();
    double dx = m_mesh.get_dx();
    double dy = m_mesh.get_dy();

    vtkFile << "# vtk DataFile Version 3.0\n2D Heat Diffusion\nBINARY\nDATASET STRUCTURED_POINTS\n";
    vtkFile << "DIMENSIONS " << nx << " " << ny << " 1\n";
    vtkFile << "ORIGIN 0 0 0\n";
    vtkFile << "SPACING " << dx << " " << dy << " 1.0\n";
    
    // --- BLOCK 1: ΤΑΧΥΤΗΤΑ (VECTORS) ---
    // Το POINT_DATA μπαίνει πλέον εδώ, πριν από τα VECTORS
    vtkFile << "POINT_DATA " << nx * ny << "\n";
    vtkFile << "VECTORS velocity double\n"; // Μόνο ένα \n στο τέλος

    for (int i = 0; i < ny; ++i) {
        for (int j = 0; j < nx; ++j) {
            double vx = toBigEndian(u[i][j]);
            double vy = toBigEndian(v[i][j]);
            double vz = toBigEndian(0.0);
            
            vtkFile.write(reinterpret_cast<const char*>(&vx), sizeof(double));
            vtkFile.write(reinterpret_cast<const char*>(&vy), sizeof(double));
            vtkFile.write(reinterpret_cast<const char*>(&vz), sizeof(double));
        }
    }

    // --- BLOCK 2: ΠΙΕΣΗ (SCALARS) ---
    // Προσθέτουμε ένα \n στην αρχή της εντολής κειμένου για να διαχωριστεί από τα binary δεδομένα της ταχύτητας
    vtkFile << "\nSCALARS pressure double 1\n";
    vtkFile << "LOOKUP_TABLE default\n"; // Μόνο ένα \n στο τέλος

    for (int i = 0; i < ny; ++i) {
        for (int j = 0; j < nx; ++j) {
            double val_p = toBigEndian(p[i][j]);
            vtkFile.write(reinterpret_cast<const char*>(&val_p), sizeof(double));
        }
    }

    vtkFile.close();

}