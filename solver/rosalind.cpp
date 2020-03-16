#include "rosalind.h"

#include <iostream>

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

std::vector<std::vector<std::size_t>>
rosalind::max_nonbranching_paths(const std::map<std::size_t, std::multiset<std::size_t>> &graph) {
    std::vector<std::vector<std::size_t>> paths;

    std::map<std::size_t, std::size_t> in_degree;

    for (const auto &[v, edges] : graph) {
        for (std::size_t u : edges) {
            in_degree[u]++;
        }
    }

    std::map<std::size_t, bool> used;
    for (auto &[v, edges] : graph) {
        if (in_degree[v] != 1 || edges.size() != 1) {
            if (!edges.empty()) {
                used[v] = true;
                for (std::size_t w : edges) {
                    std::vector<std::size_t> path{v, w};
                    used[w] = true;
                    while (in_degree[w] == 1 && graph.count(w) && graph.find(w)->second.size() == 1) {
                        w = *graph.find(w)->second.begin();
                        path.push_back(w);
                        used[w] = true;
                    }
                    paths.push_back(std::move(path));
                }
            }
        }
    }

    for (auto &[v, edges] : graph) {
        if (used[v]) {
            continue;
        }
        std::size_t w = *edges.begin();
        paths.push_back({v, w});
        used[w] = true;

        while (w != v) {
            w = *graph.find(w)->second.begin();
            paths.back().push_back(w);
            used[w] = true;
        }
    }

    return paths;
}

std::string rosalind::longest_common_subsequence(const std::string &a, const std::string &b) {
    std::vector<std::vector<std::size_t>> dp(a.size(), std::vector<std::size_t>(b.size(), 0));
    if (a[0] == b[0]) dp[0][0] = 1;

    for (int i = 1; i < a.size(); i++) {
        if (a[i] == b[0]) {
            dp[i][0] = 1;
        } else {
            dp[i][0] = dp[i - 1][0];
        }
    }

    for (int i = 1; i < b.size(); i++) {
        if (a[0] == b[i]) {
            dp[0][i] = 1;
        } else {
            dp[0][i] = dp[0][i - 1];
        }
    }

    for (int i = 1; i < a.size(); i++) {
        for (int j = 1; j < b.size(); j++) {
            if (a[i] == b[j]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int pi = a.size() - 1, pj = b.size() - 1;
    std::string answer;

    while (pi != -1 && pj != -1) {
        if (a[pi] == b[pj]) {
            answer.push_back(a[pi]);
            pi--;
            pj--;
        } else {
            if (pi && dp[pi][pj] == dp[pi - 1][pj]) pi--;
            else if (pj && dp[pi][pj] == dp[pi][pj - 1]) pj--;
            else pi = -1;
        }
    }

    return std::string(answer.rbegin(), answer.rend());
}

rosalind::alignment
rosalind::align_with_affine_gap(const std::string &a, const std::string &b, const int opening_penalty,
                                const int extending_penalty, std::map<char, std::map<char, int> > scoring) {
    std::vector<std::vector<int64_t>> M(a.size() + 1, std::vector<int64_t>(b.size() + 1));
    std::vector<std::vector<int64_t>> A(a.size() + 1, std::vector<int64_t>(b.size() + 1));
    std::vector<std::vector<int64_t>> B(a.size() + 1, std::vector<int64_t>(b.size() + 1));

    M[0][0] = 0;
    for (int i = 1; i <= a.size(); i++) M[i][0] = INT32_MIN;
    for (int j = 1; j <= b.size(); j++) M[0][j] = INT32_MIN;

    A[0][1] = -opening_penalty;
    for (int i = 0; i <= a.size(); i++) A[i][0] = INT32_MIN;
    for (int j = 2; j <= b.size(); j++) A[0][j] = A[0][j - 1] - extending_penalty;

    B[1][0] = -opening_penalty;
    for (int i = 2; i <= a.size(); i++) B[i][0] = B[i - 1][0] - extending_penalty;
    for (int j = 0; j <= b.size(); j++) B[0][j] = INT32_MIN;

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            M[i][j] =
                    std::max(M[i - 1][j - 1], std::max(A[i - 1][j - 1], B[i - 1][j - 1])) + scoring[a[i - 1]][b[j - 1]];
            A[i][j] = std::max(A[i][j - 1] - extending_penalty, std::max(M[i][j - 1], B[i][j - 1]) - opening_penalty);
            B[i][j] = std::max(B[i - 1][j] - extending_penalty, std::max(M[i - 1][j], A[i - 1][j]) - opening_penalty);
        }
    }

    int pi = a.size(), pj = b.size();
    char matrix = 'U';
    int max = std::max(M.back().back(), std::max(A.back().back(), B.back().back()));

    if (M.back().back() == max) matrix = 'M';
    if (A.back().back() == max) matrix = 'A';
    if (B.back().back() == max) matrix = 'B';

    std::string ra, rb;
    while (pi || pj) {
        switch (matrix) {
            case 'M': {
                int64_t prev = M[pi][pj] - scoring[a[pi - 1]][b[pj - 1]];
                if (M[pi - 1][pj - 1] == prev) matrix = 'M';
                if (A[pi - 1][pj - 1] == prev) matrix = 'A';
                if (B[pi - 1][pj - 1] == prev) matrix = 'B';

                ra.push_back(a[pi - 1]);
                rb.push_back(b[pj - 1]);
                pi--;
                pj--;
                break;
            }
            case 'A': {
                if (M[pi][pj - 1] - opening_penalty == A[pi][pj]) matrix = 'M';
                if (A[pi][pj - 1] - extending_penalty == A[pi][pj]) matrix = 'A';
                if (B[pi][pj - 1] - opening_penalty == A[pi][pj]) matrix = 'B';

                ra.push_back('-');
                rb.push_back(b[pj - 1]);
                pj--;
                break;
            }
            case 'B': {
                if (M[pi - 1][pj] - opening_penalty == B[pi][pj]) matrix = 'M';
                if (A[pi - 1][pj] - opening_penalty == B[pi][pj]) matrix = 'A';
                if (B[pi - 1][pj] - extending_penalty == B[pi][pj]) matrix = 'B';

                ra.push_back(a[pi - 1]);
                rb.push_back('-');
                pi--;
                break;
            }
        }
    }

    return {max, std::string(ra.rbegin(), ra.rend()), std::string(rb.rbegin(), rb.rend())};
}