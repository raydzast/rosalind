#include "trees_solver.h"

void trees_solver::ba7a() {
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