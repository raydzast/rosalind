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

void solver::ba3m() {
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

std::vector<std::vector<int>> read_circular(std::istream &in) {
    std::vector<std::vector<int>> result;

    char c;
    while (in.peek() != EOF && in.peek() != '\n') {
        int tmp;
        in >> c;
        std::noskipws(in);
        result.emplace_back();
        while (c != ')' && in >> tmp >> c) {
            result.back().push_back(tmp);
        }
    }
    in >> c;

    return result;
}

void print_circular(std::ostream &out, const std::vector<std::vector<int>> &p) {
    for (auto &cycle : p) {
        char pre = '(';
        for (int v : cycle) {
            out << pre << std::showpos << v;
            pre = ' ';
        }
        out << ')';
    }
    out << std::endl;
}

void solver::ba6c() {
    auto P = read_circular(in);
    auto Q = read_circular(in);

    out << rosalind::two_break_distance(P, Q) << std::endl;
}

std::vector<std::vector<int>> graph_to_permutation(const std::map<std::size_t, std::size_t> &graph) {
    std::map<std::size_t, bool> mark;
    std::function<void(std::size_t, std::vector<int> &)> dfs = [&](std::size_t u, std::vector<int> &cycle) {
        if (mark[u]) return;
        mark[u] = mark[u ^ 1] = true;

        if (cycle.empty()) {
            cycle.push_back(u / 2 + 1);
        } else {
            bool inv = graph.find(u)->second % 2 == u % 2;
            int sgn = ((cycle.back() < 0) ^ inv) ? -1 : 1;
            cycle.push_back((u / 2 + 1) * sgn);
        }

        dfs(graph.find(u ^ 1)->second, cycle);
    };

    std::vector<std::vector<int>> result;
    for (auto &[u, v] : graph) {
        if (!mark[u]) {
            result.emplace_back();
            dfs(u, result.back());
        }
    }

    return result;
}

std::vector<std::vector<int>>
two_break_on_circular(const std::vector<std::vector<int>> &P,
                      std::size_t a, std::size_t b, std::size_t c, std::size_t d) {
    auto graph = rosalind::connection_graph(P);
    graph[a] = c;
    graph[c] = a;
    graph[b] = d;
    graph[d] = b;
    return graph_to_permutation(graph);
}

void solver::ba6d() {
    auto P = read_circular(in);
    auto Q = read_circular(in);

    while (rosalind::two_break_distance(P, Q) != 0) {
        for (auto &c : rosalind::cycles(P, Q)) {
            if (4 <= c.size()) {
                print_circular(out, P);
                P = two_break_on_circular(P, c[0], c[1], c[3], c[2]);
                break;
            }
        }
    }
    print_circular(out, P);
}


void solver::ba7a() {
    int n;
    in >> n;
    std::map<int, std::size_t> ids;
    char c;
    std::size_t u, v;
    int64_t w;

    std::vector<std::pair<std::pair<std::size_t, std::size_t>, int64_t>> edges;

    while (in >> u >> c >> c >> v >> c >> w) {
        if (!ids.count(u)) ids[u] = ids.size();
        if (!ids.count(v)) ids[v] = ids.size();

        edges.push_back({{ids[u], ids[v]}, w});
    }

    std::vector<std::set<std::size_t>> neighbours(ids.size());
    std::vector<std::vector<int64_t>> dist(ids.size(), std::vector<int64_t>(ids.size(), INT32_MAX));

    for (auto &[ends, w] : edges) {
        auto [u, v] = ends;
        neighbours[u].insert(v);
        neighbours[v].insert(u);

        dist[u][v] = w;
    }

    for (std::size_t i = 0; i < dist.size(); i++) {
        dist[i][i] = 0;
    }

    for (std::size_t k = 0; k < dist.size(); k++) {
        for (std::size_t i = 0; i < ids.size(); i++) {
            for (std::size_t j = 0; j < ids.size(); j++) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    std::vector<std::size_t> leaves;
    for (int i = 0; i < ids.size(); i++) {
        if (neighbours[i].size() == 1) leaves.push_back(i);
    }

    for (int i = 0; i < leaves.size(); i++) {
        for (int j = 0; j < leaves.size(); j++) {
            out << dist[leaves[i]][leaves[j]] << " ";
        }
        out << std::endl;
    }
}