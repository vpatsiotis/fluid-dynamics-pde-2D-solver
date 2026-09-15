#pragma once
#include <vector>
#include <string>
#include "mesh.h" // Υποθέτουμε ότι εδώ ορίζεται η κλάση mesh_ref

class visual {
private:
    const mesh& m_mesh; // Κρατάμε αναφορά στο mesh για τις διαστάσεις

public:
    visual(const mesh& mesh_ref);

    // Η συνάρτηση δέχεται το χρονικό βήμα και τα πεδία u, v, p για αποθήκευση
    void vtkFile(int step, const std::vector<std::vector<double>>& u, const std::vector<std::vector<double>>& v,  const std::vector<std::vector<double>>& p);
};