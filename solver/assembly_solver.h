#ifndef ROSALIND_ASSEMBLY_SOLVER_H
#define ROSALIND_ASSEMBLY_SOLVER_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "abstract_solver.h"
#include "rosalind.h"


class assembly_solver : public virtual abstract_solver {
public:
    void ba3c();

    void ba3d();

    void ba3h();

    void ba3k();

    void ba3m();
};


#endif //ROSALIND_ASSEMBLY_SOLVER_H
