#ifndef ALIGNMENT_SOLVER_H
#define ALIGNMENT_SOLVER_H

#include <algorithm>
#include <string>
#include <vector>

#include "abstract_solver.h"
#include "rosalind.h"


class alignment_solver : public virtual abstract_solver {
public:
    void ba5c();

    void ba5e();

    void ba5j();

    void ba5m();
};

#endif //ALIGNMENT_SOLVER_H