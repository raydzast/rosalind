#include "alignment_solver.h"

void alignment_solver::ba5c() {
    std::string a, b;
    in >> a >> b;

    out << rosalind::longest_common_subsequence(a, b) << std::endl;
}

void alignment_solver::ba5e() {
    std::string a, b;
    in >> a >> b;

#include "../assets/BLOSUM62"

    const int gap_score = 5;

    std::vector<std::vector<int>> dp(a.size() + 1, std::vector<int>(b.size() + 1, 0));

    for (int i = 1; i <= a.size(); i++) {
        dp[i][0] = dp[i - 1][0] - gap_score;
    }

    for (int i = 1; i <= b.size(); i++) {
        dp[0][i] = dp[0][i - 1] - gap_score;
    }

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            dp[i][j] = std::max(dp[i - 1][j - 1] + scoring[a[i - 1]][b[j - 1]],
                                std::max(dp[i - 1][j], dp[i][j - 1]) - gap_score);
        }
    }

//    for (int i = 0; i < dp.size(); i++) {
//        for (int j = 0; j < dp[i].size(); j++) {
//            out << dp[i][j] << "\t";
//        }
//        out << std::endl;
//    }

    std::string ra, rb;
    int pi = a.size(), pj = b.size();
    while (pi || pj) {
        if (pi == 0) {
            ra.push_back('-');
            rb.push_back(b[pj - 1]);
            pj--;
            continue;
        }
        if (pj == 0) {
            ra.push_back(a[pi - 1]);
            rb.push_back('-');
            pi--;
            continue;
        }

        if (dp[pi][pj] == dp[pi][pj - 1] - gap_score) {
            ra.push_back('-');
            rb.push_back(b[pj - 1]);
            pj--;
            continue;
        }
        if (dp[pi][pj] == dp[pi - 1][pj] - gap_score) {
            ra.push_back(a[pi - 1]);
            rb.push_back('-');
            pi--;
            continue;
        }
        if (dp[pi][pj] == dp[pi - 1][pj - 1] + scoring[a[pi - 1]][b[pj - 1]]) {
            ra.push_back(a[pi - 1]);
            rb.push_back(b[pj - 1]);
            pi--;
            pj--;
            continue;
        }
    }

    out << dp.back().back() << std::endl;
    out << std::string(ra.rbegin(), ra.rend()) << std::endl;
    out << std::string(rb.rbegin(), rb.rend()) << std::endl;
}