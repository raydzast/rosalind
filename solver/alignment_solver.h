#ifndef ROSALIND_ALIGNMENT_SOLVER_H
#define ROSALIND_ALIGNMENT_SOLVER_H

#include <algorithm>
#include <string>
#include <vector>

#include "abstract_solver.h"
#include "rosalind.h"


class alignment_solver : public virtual abstract_solver {
public:
    void ba5c();
};

#endif //ROSALIND_ALIGNMENT_SOLVER_H