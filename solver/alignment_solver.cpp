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

    auto result = rosalind::align_with_affine_gap(a, b, 5, 5, scoring);
    out << result.val << std::endl;
    out << result.a << std::endl;
    out << result.b << std::endl;
}

void alignment_solver::ba5j() {
    std::string a, b;
    in >> a >> b;

#include "../assets/BLOSUM62"

    rosalind::alignment result = rosalind::align_with_affine_gap(a, b, 11, 1, scoring);
    out << result.val << std::endl;
    out << result.a << std::endl;
    out << result.b << std::endl;
}

void alignment_solver::ba5m() {
    std::string a, b, c;
    in >> a >> b >> c;

    auto ***dp = new int64_t **[a.size() + 1];
    for (int i = 0; i <= a.size(); i++) {
        dp[i] = new int64_t *[b.size() + 1];
        for (int j = 0; j <= b.size(); j++) {
            dp[i][j] = new int64_t[c.size() + 1];
            for (int k = 0; k <= c.size(); k++) {
                dp[i][j][k] = 0;
            }
        }
    }

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            for (int k = 1; k <= c.size(); k++) {
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                }

                for (uint8_t mask = 1; mask < 8; mask++) {
                    bool di = (mask & 1) != 0;
                    bool dj = (mask & 2) != 0;
                    bool dk = (mask & 4) != 0;
                    dp[i][j][k] = std::max(dp[i][j][k], dp[i - di][j - dj][k - dk]);
                }
            }
        }
    }

    out << dp[a.size()][b.size()][c.size()] << std::endl;

    std::string ra, rb, rc;
    int pi = a.size(), pj = b.size(), pk = c.size();
    while (pi || pj || pk) {
        bool found = false;

        for (int mask : {7, 6, 5, 3, 4, 2, 1}) {
            bool di = (mask & 1) != 0;
            bool dj = (mask & 2) != 0;
            bool dk = (mask & 4) != 0;
            if (!pi && di) continue;
            if (!pj && dj) continue;
            if (!pk && dk) continue;

            if (dp[pi - di][pj - dj][pk - dk] == dp[pi][pj][pk]) {
                ra.push_back(di ? a[pi - 1] : '-');
                rb.push_back(dj ? b[pj - 1] : '-');
                rc.push_back(dk ? c[pk - 1] : '-');

                pi = pi - di;
                pj = pj - dj;
                pk = pk - dk;

                found = true;
                break;
            }
        }

        if (!found) {
            ra.push_back(a[pi - 1]);
            rb.push_back(b[pj - 1]);
            rc.push_back(c[pk - 1]);

            pi = pi - 1;
            pj = pj - 1;
            pk = pk - 1;
        }
    }

    std::reverse(ra.begin(), ra.end());
    std::reverse(rb.begin(), rb.end());
    std::reverse(rc.begin(), rc.end());

    out << ra << std::endl;
    out << rb << std::endl;
    out << rc << std::endl;
}