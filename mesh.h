#pragma once
#include <vector>

class mesh
{
private:
    int nx, ny; // Numbers of Points
    double dx, dy;  // Cell Size
    // Cell Center and Faces
    std::vector <std::vector <double>> X, Y, x_face, y_face;

public:
    // Constructor
    mesh(int _nx, int _ny, double _dx, double _dy);

    // Method
    void generate_grid();

    // Getters
    int get_nx() const { return nx; }
    int get_ny() const { return ny; }
    double get_dx() const { return dx; }
    double get_dy() const { return dy; }

    // GETTERS για τους vectors (επιστρέφονται ως const reference για μέγιστη ταχύτητα)
    const std::vector<std::vector<double>>& get_X() const { return X; }
    const std::vector<std::vector<double>>& get_Y() const { return Y; }
    const std::vector<std::vector<double>>& get_x_face() const { return x_face; }
    const std::vector<std::vector<double>>& get_y_face() const { return y_face; }
};


