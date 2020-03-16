#include <iostream>
#include <vector>
#include <sstream>
#include <map>

int main() {
    std::freopen("../assets/BLOSUM62.txt", "r+", stdin);
    std::freopen("../assets/BLOSUM62", "w+", stdout);

    std::vector<char> keys;
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss;
    ss << line;

    char tmp;
    while (ss >> tmp) {
        keys.push_back(tmp);
    }

    std::map<char, std::map<char, int>> scoring;
    while (std::getline(std::cin, line)) {
        ss.clear();
        ss << line;

        int value;
        ss >> tmp;
        for (char key : keys) {
            ss >> value;
            scoring[tmp][key] = value;
        }
    }

    std::cout << "std::map<char, std::map<char, int>> scoring = ";
    std::string bef = "{";
    for (auto [c, ps] : scoring) {
        std::cout << bef << "{'" << c << "',";
        bef = "{";

        for (auto [z, v] : ps) {
            std::cout << bef << "{'" << z << "', " << v << "}";
            bef = ",";
        }
        std::cout << "}}";
        bef = ",";
    }
    std::cout << "};" << std::endl;
    return 0;
}