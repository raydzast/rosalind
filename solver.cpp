#include "solver.h"

solver::solver(std::istream &in, std::ostream &out) : in(in), out(out) {}

void solver::ba3c() {
    std::vector<std::string> patterns;

    std::string tmp;
    while (std::getline(in, tmp)) {
        patterns.push_back(std::move(tmp));
    }

    auto graph = rosalind::overlap(patterns);
    for (int u = 0; u < graph.size(); u++) {
        for (auto v : graph[u]) {
            out << patterns[u] << " -> " << patterns[v] << std::endl;
        }
    }
}

void solver::ba3d() {
    int k;
    std::string text;
    in >> k >> text;

    auto graph = rosalind::debrujin(k, text);

    for (auto &[u, g] : graph) {
        if (g.empty()) {
            continue;
        }

        out << u << " -> " << *g.begin();
        for (auto it = ++g.begin(); it != g.end(); it++) {
            out << ',' << *it;
        }
        out << std::endl;
    }
}

void solver::ba3h() {
    int k;
    std::vector<std::string> patterns;
    in >> k;
    in.ignore(1);

    std::string tmp;
    while (std::getline(in, tmp)) {
        patterns.push_back(std::move(tmp));
    }

    auto graph = rosalind::overlap(patterns);

    std::map<std::string_view, std::size_t> ids;
    for (int i = 0; i < patterns.size(); i++) {
        ids[patterns[i]] = i;
    }

    auto path = rosalind::eulerian_path(graph);

    std::string result = patterns[path.front()].substr(0, k - 1);
    for (auto id : path) {
        result.push_back(patterns[id].back());
    }

    out << result << std::endl;
}

void solver::ba6a() {
    std::noskipws(in);
    std::vector<int> permutation;

    char ignored;
    int tmp;
    while (in >> ignored >> tmp) {
        permutation.push_back(tmp);
    }

    for (auto &p : rosalind::greedy_sort_permutation(permutation)) {
        char pre = '(';
        for (int v : p) {
            out << pre << std::showpos << v;
            pre = ' ';
        }
        out << ')' << std::endl;
    }
}

void solver::ba6b() {
    std::noskipws(in);
    std::vector<int> permutation;

    char ignored;
    int tmp;
    while (in >> ignored >> tmp) {
        permutation.push_back(tmp);
    }

    out << rosalind::permutation_breakpoints_count(permutation) << std::endl;
}