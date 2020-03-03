#include "abstract_solver.h"

abstract_solver::abstract_solver() : abstract_solver(std::cin, std::cout) {}

abstract_solver::abstract_solver(std::istream &in, std::ostream &out) : in(in), out(out) {}

abstract_solver::~abstract_solver() = default;