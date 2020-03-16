#include "alignment_solver.h"

void alignment_solver::ba5c() {
    std::string a, b;
    in >> a >> b;

    out << rosalind::longest_common_subsequence(a, b) << std::endl;
}

void alignment_solver::ba5e() {
    std::string a, b;
    in >> a >> b;

#include "../assets/BLOSUM62"

    auto result = rosalind::align_with_affine_gap(a, b, 5, 5, scoring);
    out << result.val << std::endl;
    out << result.a << std::endl;
    out << result.b << std::endl;
}

void alignment_solver::ba5j() {
    std::string a, b;
    in >> a >> b;

#include "../assets/BLOSUM62"

    rosalind::alignment result = rosalind::align_with_affine_gap(a, b, 11, 1, scoring);
    out << result.val << std::endl;
    out << result.a << std::endl;
    out << result.b << std::endl;
}