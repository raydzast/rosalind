#ifndef ROSALIND_COMMON_SOLVER_H
#define ROSALIND_COMMON_SOLVER_H

#include <iostream>

#include "alignment_solver.h"
#include "assembly_solver.h"
#include "recombination_solver.h"
#include "trees_solver.h"


class common_solver 
        : public assembly_solver, public recombination_solver, public trees_solver, public alignment_solver {
public:
    common_solver(std::istream &in, std::ostream &out);
};


#endif //ROSALIND_COMMON_SOLVER_H
