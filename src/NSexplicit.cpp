#include "NSexplicit.h"
#include <iostream>
#include <vector>
#include <algorithm>

NSexplicit::NSexplicit(const mesh& mesh, boundary& bc, double dt, double visc, double rho, double nt, int write_interval)
    :mesh_ref(mesh), bc_ref(bc), dt(dt), m(visc), nt(nt), rho(rho), write_interval(write_interval)
{
    this->nx = mesh_ref.get_nx(); 
    this->ny = mesh_ref.get_ny();

    u.assign(ny, std::vector<double>(nx, 0.0));
    un.assign(ny, std::vector<double>(nx, 0.0));
    v.assign(ny, std::vector<double>(nx, 0.0));
    vn.assign(ny, std::vector<double>(nx, 0.0));
    p.assign(ny, std::vector<double>(nx, 0.0));
    pn.assign(ny, std::vector<double>(nx, 0.0));
}

void NSexplicit::calc()
{
    double dx = mesh_ref.get_dx();
    double dy = mesh_ref.get_dy();

    std::vector<std::vector<double>> S(ny, std::vector<double>(nx, 0.0));

    for (int n = 1; n < nt + 1; ++n)
    {
        for (int i = 1; i < ny - 1; ++i)
        {
            for (int j = 1; j < nx - 1; ++j)
            {
                // Diffusion Terms - X momentum
                double De_x = m * (u[i][j+1] - u[i][j]) / (dx * dx);
                double Dw_x = m * (u[i][j] - u[i][j-1]) / (dx * dx);
                double Dn_x = m * (u[i+1][j] - u[i][j]) / (dy * dy);
                double Ds_x = m * (u[i][j] - u[i-1][j]) / (dy * dy);

                // Diffusion Terms - Y momentum
                double De_y = m * (v[i][j+1] - v[i][j]) / (dx * dx);
                double Dw_y = m * (v[i][j] - v[i][j-1]) / (dx * dx);
                double Dn_y = m * (v[i+1][j] - v[i][j]) / (dy * dy);
                double Ds_y = m * (v[i][j] - v[i-1][j]) / (dy * dy);

                // Convection Terms - X momentum
                // --- CONVECTION TERMS (Upwind Scheme για Collocated Grid) ---

                // 1. Ροές Μάζας στις διεπαφές (Mass fluxes - Μέσοι όροι)
                double u_e = (u[i][j+1] + u[i][j]) / 2.0;
                double u_w = (u[i][j] + u[i][j-1]) / 2.0;
                double v_n = (v[i+1][j] + v[i][j]) / 2.0;
                double v_s = (v[i][j] + v[i-1][j]) / 2.0;

                // 2. X-momentum Convection (Μεταφορά της u)
                double Fe_x = rho * u_e * (u_e > 0 ? u[i][j] : u[i][j+1]) / dx;
                double Fw_x = rho * u_w * (u_w > 0 ? u[i][j-1] : u[i][j]) / dx;
                double Fn_x = rho * v_n * (v_n > 0 ? u[i][j] : u[i+1][j]) / dy;
                double Fs_x = rho * v_s * (v_s > 0 ? u[i-1][j] : u[i][j]) / dy;

                // 3. Y-momentum Convection (Μεταφορά της v)
                double Fe_y = rho * u_e * (u_e > 0 ? v[i][j] : v[i][j+1]) / dx;
                double Fw_y = rho * u_w * (u_w > 0 ? v[i][j-1] : v[i][j]) / dx;
                double Fn_y = rho * v_n * (v_n > 0 ? v[i][j] : v[i+1][j]) / dy;
                double Fs_y = rho * v_s * (v_s > 0 ? v[i-1][j] : v[i][j]) / dy;

                // Predictor Step
                un[i][j] = u[i][j] + (dt / rho) * ( - (Fe_x - Fw_x + Fn_x - Fs_x) + (De_x - Dw_x + Dn_x - Ds_x) );
                vn[i][j] = v[i][j] + (dt / rho) * ( - (Fe_y - Fw_y + Fn_y - Fs_y) + (De_y - Dw_y + Dn_y - Ds_y) );

            }
        }
        bc_ref.velocity_boundary(mesh_ref, un, vn);

        for (int i = 1; i < ny - 1; ++i)
        {
            for (int j = 1; j < nx - 1; ++j)
            {    
                double ue, uw, vn_f, vs;
                // Rhie - Chow Discretization
                 // Rhie - Chow Discretization for X-velocity (ue, uw)
                // Σωστός χειρισμός στα όρια για Collocated Grid
                // Rhie - Chow για X-velocity
                if ((j >= 2) && (j <= nx - 3)) {
                    ue = 0.5 * (un[i][j] + un[i][j+1]) + (dt / dx) * (0.25 * (p[i][j+1] - p[i][j-1] + p[i][j+2] - p[i][j]) - (p[i][j+1] - p[i][j]));
                    uw = 0.5 * (un[i][j] + un[i][j-1]) + (dt / dx) * (0.25 * (p[i][j] - p[i][j-2] + p[i][j+1] - p[i][j-1]) - (p[i][j] - p[i][j-1]));
                } else {
                    ue = 0.5 * (un[i][j] + un[i][j+1]);
                    uw = 0.5 * (un[i][j] + un[i][j-1]);                    
                }

                // Αν είσαι ακριβώς στο δεξί τοίχωμα, η ροή ue είναι 0
                if (j == nx - 2) ue = un[i][nx-1];
                // Αν είσαι ακριβώς στο αριστερό τοίχωμα, η ροή uw είναι 0
                if (j == 1) uw = un[i][0];


                // Rhie - Chow για Y-velocity
                if ((i >= 2) && (i <= ny - 3)) {
                    vn_f = 0.5 * (vn[i][j] + vn[i+1][j]) + (dt / dy) * (0.25 * (p[i+1][j] - p[i-1][j] + p[i+2][j] - p[i][j]) - (p[i+1][j] - p[i][j]));
                    vs   = 0.5 * (vn[i][j] + vn[i-1][j]) + (dt / dy) * (0.25 * (p[i][j] - p[i-2][j] + p[i+1][j] - p[i-1][j]) - (p[i][j] - p[i-1][j]));
                } else {
                    vn_f = 0.5 * (vn[i][j] + vn[i+1][j]);
                    vs   = 0.5 * (vn[i][j] + vn[i-1][j]);                    
                }

                // Αν είσαι ακριβώς στο πάνω ή κάτω τοίχωμα, οι κάθετες ροές είναι 0
                if (i == ny - 2) vn_f = 0.0;
                if (i == 1) vs = 0.0;

                S[i][j] = (rho / dt) * (((ue - uw) / dx) + ((vn_f - vs) / dy));
            }
        }
    
        // Poisson Solver for Pressure - Gauss Seidel Method
        double error = 0.1;
        double tolerance = 0.0001;
        double omega = 1.7;
        int iter = 0;
        int max_iter = 500;

        if(n%100 == 0){
        // ΠΡΙΝ ΤΟ WHILE: Έλεγχος αν η πηγή S έχει λογικές τιμές
        std::cout << "Time step n=" << n << " | Max S: " << S[1][1] << std::endl;}

        while (error >= tolerance && iter < max_iter)
        {
            error = 0.0;
            for (int i = 1; i < ny - 1; ++i)
            {
                for (int j = 1; j < nx - 1; ++j)
                {
                    double old_p = p[i][j];
                    double p_GS = ((dy*dy)*(p[i][j+1] + pn[i][j-1]) + (dx*dx)*(p[i+1][j] + pn[i-1][j]) - S[i][j]*(dx*dx)*(dy*dy)) / (2.0*((dx * dx) + (dy * dy)));
                    
                    pn[i][j] = (1 - omega) * old_p + omega*p_GS;

                    // Υπολογισμός της διαφοράς για το συγκεκριμένο σημείο
                    double diff = std::abs(pn[i][j] - p[i][j]);

                    // Κρατάμε τη μέγιστη διαφορά (L-infinity norm)
                    if (diff > error)
                    {
                        error = diff;
                    }
                }               
            }

            bc_ref.pressure_boundary(mesh_ref, pn);
            iter++;        
            p = pn;
        }
        if (n%100 == 0){
        // ΜΕΤΑ ΤΟ WHILE: Έλεγχος αν η πίεση εκτινάχθηκε
        std::cout << "Poisson finished at iter: " << iter << " | Error: " << error << std::endl;}

        for (int i = 1; i < ny - 1; ++i)
        {
            for (int j = 1; j < nx - 1; ++j)
            {
                // Διόρθωση της X-ταχύτητας (u) χρησιμοποιώντας το gradient της πίεσης στον άξονα X
                u[i][j] = un[i][j] - (dt / (rho * dx)) * (p[i][j] - p[i][j-1]);
                // Διόρθωση της Y-ταχύτητας (v) χρησιμοποιώντας το gradient της πίεσης στον άξονας Y
                v[i][j] = vn[i][j] - (dt / (rho * dy)) * (p[i][j] - p[i-1][j]);
            }
        }

        bc_ref.velocity_boundary(mesh_ref, u, v);


        if (n % write_interval == 0)
        {
            visual vtk1(mesh_ref);
            vtk1.vtkFile(n,u,v,p);
        }
    }
}