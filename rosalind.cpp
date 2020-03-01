#include "rosalind.h"

std::vector<std::multiset<std::size_t>>
rosalind::overlap(const std::vector<std::string> &patterns) {
    std::vector<std::multiset<std::size_t>> graph(patterns.size());

    std::map<std::string_view, std::multiset<std::size_t>> prefixes;
    for (int i = 0; i < patterns.size(); i++) {
        std::string_view view(patterns[i]);
        prefixes[view.substr(0, view.size() - 1)].insert(i);
    }

    for (int i = 0; i < patterns.size(); i++) {
        std::string_view view(patterns[i]);
        graph[i] = prefixes[view.substr(1, view.size() - 1)];
    }

    return graph;
}

std::vector<std::pair<std::string_view, std::string_view>>
rosalind::pathGraph(std::size_t k, const std::string &text) {
    std::vector<std::pair<std::string_view, std::string_view>> path;
    std::string_view view(text);

    for (int i = 0; i <= text.size() - k; i++) {
        path.emplace_back(view.substr(i, k - 1), view.substr(i + 1, k - 1));
    }

    return path;
}

std::map<std::string_view, std::set<std::string_view>>
rosalind::debrujin(std::size_t k, const std::string &text) {
    std::map<std::string_view, std::set<std::string_view>> result;

    for (auto &[u, v] : pathGraph(k, text)) {
        result[u].insert(v);
    }

    return result;
}

std::vector<std::size_t>
rosalind::eulerian_path(const std::vector<std::multiset<std::size_t>> &graph) {
    std::set<std::size_t> vs;
    std::unordered_map<std::size_t, std::size_t> degree;

    for (int u = 0; u < graph.size(); u++) {
        vs.insert(u);
        degree[u] += graph[u].size();
        for (int v : graph[u]) {
            vs.insert(v);
            degree[v]++;
        }
    }

    std::vector<std::multiset<std::size_t>> graph_copy(graph);

    std::size_t start = -1;
    for (auto &v : vs) {
        if (degree[v] % 2 == 1 && !graph_copy[v].empty()) {
            start = v;
        }
    }

    std::stack<std::size_t> s;
    s.push(start);
    std::vector<std::size_t> path;

    while (!s.empty()) {
        auto w = s.top();
        for (auto &v : vs) {
            if (graph_copy[w].find(v) != graph_copy[w].end()) {
                s.push(v);
                graph_copy[w].erase(v);
                break;
            }
        }
        if (w == s.top()) {
            s.pop();
            path.push_back(w);
        }
    }

    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<std::vector<int>>
rosalind::greedy_sort_permutation(const std::vector<int> &source) {
    std::vector<std::vector<int>> result;
    std::vector<int> tmp(source.begin(), source.end());

    int p = 0;
    while (p < source.size()) {
        int k = -1;
        for (int i = p; i < tmp.size(); i++) {
            if (abs(tmp[i]) == p + 1) {
                k = i;
                break;
            }
        }

        if (k == -1) {
            break;
        }

        std::reverse(tmp.begin() + p, tmp.begin() + k + 1);
        for (int i = p; i <= k; i++) {
            tmp[i] = -tmp[i];
        }
        result.push_back(tmp);
        while (tmp[p] == p + 1) p++;
    }

    return result;
}

std::size_t
rosalind::permutation_breakpoints_count(const std::vector<int> &source) {
    std::size_t answer = 0;

    std::vector<int> tmp(1, 0);
    std::copy(source.begin(), source.end(), std::back_inserter(tmp));
    tmp.push_back(source.size() + 1);
    for (int i = 1; i < tmp.size(); i++) {
        answer += tmp[i - 1] + 1 != tmp[i];
    }

    return answer;
}

std::map<std::size_t, std::size_t>
rosalind::connection_graph(const std::vector<std::vector<int>> &p) {
    std::map<std::size_t, std::size_t> graph;

    for (auto &cycle : p) {
        int u = (abs(cycle.back()) - 1) * 2 + (0 < cycle.back());
        int v = (abs(cycle[0]) - 1) * 2 + (cycle[0] < 0);
        graph[u] = v;
        graph[v] = u;

        for (int i = 1; i < cycle.size(); i++) {
            u = (abs(cycle[i - 1]) - 1) * 2 + (0 < cycle[i - 1]);
            v = (abs(cycle[i]) - 1) * 2 + (cycle[i] < 0);
            graph[u] = v;
            graph[v] = u;
        }
    }

    return graph;
}

std::vector<std::vector<std::size_t>>
rosalind::cycles(const std::vector<std::vector<int>> &P, const std::vector<std::vector<int>> &Q) {
    auto cgP = connection_graph(P);
    auto cgQ = connection_graph(Q);

    std::vector<std::vector<std::size_t>> result;
    std::vector<bool> mark(cgP.size(), false);
    std::function<void(int, std::vector<std::size_t> &)> dfs = [&](int u, std::vector<std::size_t> &cycle) {
        if (mark[u]) return;
        mark[u] = mark[cgP[u]] = true;

        cycle.push_back(u);
        cycle.push_back(cgP[u]);

        dfs(cgQ[cgP[u]], cycle);
    };

    for (int i = 0; i < cgP.size(); i++) {
        if (!mark[i]) {
            result.emplace_back();
            dfs(i, result.back());
        }
    }

    return result;
}

std::size_t
rosalind::two_break_distance(const std::vector<std::vector<int>> &P, const std::vector<std::vector<int>> &Q) {
    return cycles(P, P).size() - cycles(P, Q).size();
}
