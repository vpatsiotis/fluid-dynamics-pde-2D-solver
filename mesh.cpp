# include "mesh.h"

mesh::mesh(int _nx, int _ny, double _dx, double _dy)
    :nx(_nx), ny(_ny), dx(_dx), dy(_dy)
{
    X.assign(ny, std::vector<double>(nx, 0.0));
    Y.assign(ny, std::vector<double>(nx, 0.0));
    x_face.assign(ny, std::vector<double>(nx-1,0.0));
    y_face.assign(ny-1, std::vector<double>(nx,0.0));
}

void mesh::generate_grid()
{
    for (int i = 0; i < ny; ++i)
    {
        for (int j = 0; j < nx; ++j)
        {
            X[i][j] = j*dx;
            Y[i][j] = i*dy;
        }
    }

    for (int i = 0; i < ny; ++i)
    {
        for (int j = 0; j < nx - 1; ++j) 
        {
            x_face[i][j] = (X[i][j + 1] + X[i][j]) / 2.0;
        }
    }

    for (int i = 0; i < ny - 1; ++i) 
    {
        for (int j = 0; j < nx; ++j) 
        {
            y_face[i][j] = (Y[i + 1][j] + Y[i][j]) / 2.0;
        }
    }

    // 3. Υπολογισμός αποστάσεων από Κέντρο σε Κέντρο για τα εσωτερικά κελιά
    //for (int i = 0; i < ny; ++i)
    //{
        //for (int j = 0; j < nx; ++j)
        //{
        // --- ΑΞΟΝΑΣ X (Ομοιόμορφος) ---
        //if (j == 0)        dxw[i][j] = dx; // Συνοριακό κελί (αριστερά)
        //else               dxw[i][j] = X[i][j] - X[i][j - 1];

        //if (j == nx - 1)   dxe[i][j] = dx; // Συνοριακό κελί (δεξιά)
        //else               dxe[i][j] = X[i][j + 1] - X[i][j];

        // --- ΑΞΟΝΑΣ Y (Μη-ομοιόμορφος / Εκθετικός) ---
        //if (i == 0)        dys[i][j] = Y[i][j]; // Απόσταση από τον κάτω τοίχο (y=0)
        //else               dys[i][j] = Y[i][j] - Y[i - 1][j];

        //if (i == ny - 1)   dyn[i][j] = pipe_height - Y[i][j]; // Απόσταση από τον πάνω τοίχο
        //else               dyn[i][j] = Y[i + 1][j] - Y[i][j];
        //}
    //}
}