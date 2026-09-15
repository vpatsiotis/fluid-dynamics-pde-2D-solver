#include "visual.h"
#include <string>
#include <vector>
#include <fstream>

visual::visual(const mesh& mesh)
    :m_mesh(mesh)
{
}

void visual::vtkFile(int current_nt, const std::vector<std::vector<double>>& u, const std::vector<std::vector<double>>& v, const std::vector<std::vector<double>>& p)
{
    std::string filename = "cavity2" + std::to_string(current_nt) + ".vtk";
    std::ofstream vtkFile(filename);
    
    int nx = m_mesh.get_nx();
    int ny = m_mesh.get_ny();
    double dx = m_mesh.get_dx();
    double dy = m_mesh.get_dy();

    vtkFile << "# vtk DataFile Version 3.0\n2D Heat Diffusion\nASCII\nDATASET STRUCTURED_POINTS\n";
    vtkFile << "DIMENSIONS " << nx << " " << ny << " 1\n";
    vtkFile << "ORIGIN 0 0 0\n";
    vtkFile << "SPACING " << dx << " " << dy << " 1.0\n";
    vtkFile << "POINT_DATA " << nx * ny << "\nSCALARS Temperature double\nLOOKUP_TABLE default\n";
    
    // 2. ΑΠΟΘΗΚΕΥΣΗ ΤΑΧΥΤΗΤΑΣ (Ως VECTOR: u, v, w=0)
    vtkFile << "VECTORS velocity double\n";
    for (int i = 0; i < ny; ++i) {
        for (int j = 0; j < nx; ++j) {
            // Το ParaView απαιτεί 3 συνιστώσες για τα vectors (X, Y, Z)
            vtkFile << u[i][j] << " " << v[i][j] << " 0.0\n";
        }
    }
    vtkFile << "\n";

    // 3. ΑΠΟΘΗΚΕΥΣΗ ΠΙΕΣΗΣ (Ως SCALAR)
    vtkFile << "SCALARS pressure double 1\n";
    vtkFile << "LOOKUP_TABLE default\n";
    for (int i = 0; i < ny; ++i) {
        for (int j = 0; j < nx; ++j) {
            vtkFile << p[i][j] << "\n";
        }
    }

    vtkFile.close();
}