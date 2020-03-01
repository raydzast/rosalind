#ifndef ROSALIND_EASY_SOLVER_H
#define ROSALIND_EASY_SOLVER_H

#include <iostream>

#include "rosalind.h"


class solver {
private:
    std::istream &in;
    std::ostream &out;

public:
    explicit solver(std::istream &in = std::cin, std::ostream &out = std::cout);

    void ba3c();

    void ba3d();

    void ba3h();

    void ba3k();

    void ba3m();

    void ba6a();

    void ba6b();

    void ba6c();
};


#endif //ROSALIND_EASY_SOLVER_H
