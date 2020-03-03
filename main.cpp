#include <iostream>
#include <fstream>

#include "solver/common_solver.h"

#define XSTR(s) STR(s)
#define STR(s) std::string(#s)

int main() {
    std::ifstream fin("../inputs/" + XSTR(NAME) + ".txt");
    std::ofstream fout("../outputs/" + XSTR(NAME) + ".txt");

    common_solver(fin, fout).NAME();

    return 0;
}