
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<bitset<1024>> dp(m * n);

        dp[0][grid[0][0]] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0)
                    continue;

                int idx = i * n + j;
                int val = grid[i][j];

                if (i > 0) {
                    int up = (i - 1) * n + j;

                    for (int x = 0; x < 1024; x++) {
                        if (dp[up][x]) {
                            dp[idx][x ^ val] = 1;
                        }
                    }
                }

                if (j > 0) {
                    int left = i * n + (j - 1);

                    for (int x = 0; x < 1024; x++) {
                        if (dp[left][x]) {
                            dp[idx][x ^ val] = 1;
                        }
                    }
                }
            }
        }

        int last = m * n - 1;

        for (int x = 0; x < 1024; x++) {
            if (dp[last][x])
                return x;
        }

        return -1;
    }
};
