#ifndef ROSALIND_H
#define ROSALIND_H

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <stack>


class rosalind {
public:
    rosalind() = delete;

    static std::vector<std::multiset<std::size_t>> overlap(const std::vector<std::string> &patterns);

    static std::vector<std::pair<std::string_view, std::string_view>> pathGraph(std::size_t k, const std::string &text);

    static std::map<std::string_view, std::set<std::string_view>> debrujin(std::size_t k, const std::string &text);

    static std::vector<std::size_t> eulerian_path(const std::vector<std::multiset<std::size_t>> &graph);

    static std::vector<std::vector<int>> greedy_sort_permutation(const std::vector<int> &source);
};


#endif //ROSALIND_H
