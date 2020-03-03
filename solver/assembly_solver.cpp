#include "assembly_solver.h"

void assembly_solver::ba3c() {
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

void assembly_solver::ba3d() {
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

void assembly_solver::ba3h() {
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

void assembly_solver::ba3k() {
    std::vector<std::string> kmers;

    std::string tmp;
    while (in >> tmp) {
        kmers.push_back(std::move(tmp));
    }

    std::map<std::string_view, std::size_t> ids;
    std::map<std::size_t, std::multiset<std::size_t>> graph;

    for (std::string &kmer : kmers) {
        std::string_view view(kmer);
        std::string_view prefix = view.substr(0, view.size() - 1);
        std::string_view suffix = view.substr(1, view.size() - 1);

        if (!ids.count(prefix)) ids[prefix] = ids.size();
        if (!ids.count(suffix)) ids[suffix] = ids.size();

        graph[ids[prefix]].insert(ids[suffix]);
    }

    std::vector<std::string_view> fragments(ids.size());
    for (auto &[view, id] : ids) {
        fragments[id] = view;
    }

    auto paths = rosalind::max_nonbranching_paths(graph);

    for (auto &path : paths) {
        out << fragments[path.front()];
        for (std::size_t i = 1; i < path.size(); i++) {
            out << fragments[path[i]].back();
        }
        out << ' ';
    }
}

std::map<std::size_t, std::multiset<std::size_t>> read_graph(std::istream &in) {
    std::map<std::size_t, std::multiset<std::size_t>> graph;

    std::size_t v;
    std::string arrow;
    while (in >> v >> arrow) {
        std::size_t w;
        in >> w;
        graph[v - 1].insert(w - 1);

        while (in.peek() != '\n' && in.peek() != EOF) {
            char comma;
            in >> comma >> w;
            graph[v - 1].insert(w - 1);
        }
    }

    return graph;
}

void assembly_solver::ba3m() {
    auto graph = read_graph(in);
    auto paths = rosalind::max_nonbranching_paths(graph);

    for (auto &path : paths) {
        out << path.front() + 1;
        for (std::size_t i = 1; i < path.size(); i++) {
            out << " -> " << path[i] + 1;
        }
        out << std::endl;
    }
}
