# fluid-dynamics-pde-2D-solver
2D Incompressible Navier-Stokes &amp; PDE Numerical Solver in C++ and Python.

# 2D Incompressible Navier-Stokes & PDE Numerical Solver

An object-oriented, high-performance numerical solver built from first principles in **C++** and **Python** (with algorithm prototyping in **MATLAB**). This repository contains solvers for 2D incompressible Navier-Stokes equations (Lid-Driven Cavity), non-linear Burgers' equations, and elliptic PDEs (Laplace/Poisson), featuring dynamic **Adaptive Mesh Refinement (AMR)** and rigorous verification.

## 🚀 Key Features
* **Multi-Language Architecture:** Core mathematical prototypes developed in Python/MATLAB; high-gradient modules and execution loops migrated to object-oriented **C++** for memory management and raw speed.
* **Pressure-Velocity Coupling:** Implemented custom algorithms to handle elliptic Poisson pressure equations and mass conservation.
* **Adaptive Mesh Refinement (AMR):** Dynamic grid management that automatically tracks and refines zones with localized high-gradient flow profiles while coarsening uniform zones.
* **Post-Processing Ready:** Solvers export data directly to `.vtk` format for high-fidelity 2D/3D visualization in **ParaView**.

## 📐 Numerical Methodology & Physics
1. **Governing Equations:** 2D Incompressible Navier-Stokes, Non-linear Burgers', Poisson, and Laplace PDEs.
2. **Discretization:** Finite Volume Method (FVM) / Finite Difference Method (FDM) on structured computational grids.
3. **Stability Control:** Automated time-stepping tracking based on the Courant–Friedrichs–Lewy (**CFL**) condition.

## 📊 Verification & Grid Convergence Study
To ensure numerical stability and physical accuracy, the solver was subjected to a rigorous **Grid Independence Study**. 

The 2D Lid-Driven Cavity module was executed across discrete mesh densities. The resulting steady-state velocity profiles along the cavity centerlines demonstrated asymptotic convergence, ensuring that the numerical discretization schemes are spatial-resolution independent.
