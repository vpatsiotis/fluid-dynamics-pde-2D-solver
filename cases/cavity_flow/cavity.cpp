#include <iostream>
#include "mesh.h"
#include "boundary.h"
#include "visual.h"
#include "NSexplicit.h"

int main()
{
    mesh mesh1(201, 201, 0.005, 0.005);
    mesh1.generate_grid();

    boundary bc(mesh1);

    visual initial(mesh1);    

    NSexplicit first(mesh1, bc, 0.001, 0.001, 1, 20000, 2000);
    first.calc();
}