#include "alignment_solver.h"

void alignment_solver::ba5c() {
    std::string a, b;
    in >> a >> b;

    out << rosalind::longest_common_subsequence(a, b) << std::endl;
}