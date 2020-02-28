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

void solver::ba3k() {
    std::vector<std::string> patterns;

    std::string tmp;
    while (std::getline(in, tmp)) {
        patterns.push_back(std::move(tmp));
    }

    auto graph = rosalind::overlap(patterns);

    auto contigs = rosalind::contigs(graph);

    for (auto &path : contigs) {
        std::string first = patterns[path.front()];
        std::string result(first.begin(), first.end() - 1);

        for (auto v : path) {
            result.push_back(patterns[v].back());
        }

        out << result << " ";
    }

    out << std::endl;
}