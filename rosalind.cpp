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