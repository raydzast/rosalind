#ifndef ABSTRACT_SOLVER_H
#define ABSTRACT_SOLVER_H

#include <iostream>

class abstract_solver {
protected:
    std::istream &in;
    std::ostream &out;

public:
    abstract_solver();
    abstract_solver(std::istream &in, std::ostream &out);

    virtual ~abstract_solver() = 0;
};


#endif //ABSTRACT_SOLVER_H
