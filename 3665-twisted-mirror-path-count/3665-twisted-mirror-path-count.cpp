
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {

        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // right[i][j]: ways entering from left
        // down[i][j]: ways entering from above

        vector<vector<long long>> right(m, vector<long long>(n, 0));
        vector<vector<long long>> down(m, vector<long long>(n, 0));

        // Starting position
        right[0][0] = 1;

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                // Reached destination
                if (i == m - 1 && j == n - 1) {
                    continue;
                }

                // Case 1: Current cell is a mirror
                if (grid[i][j] == 1) {

                    // Entered from left -> move down
                    if (i + 1 < m) {
                        down[i + 1][j] =
                            (down[i + 1][j] + right[i][j]) % MOD;
                    }

                    // Entered from above -> move right
                    if (j + 1 < n) {
                        right[i][j + 1] =
                            (right[i][j + 1] + down[i][j]) % MOD;
                    }

                }

                // Case 2: Current cell is empty
                else {

                    // Both states can move right
                    if (j + 1 < n) {
                        right[i][j + 1] =
                            (right[i][j + 1] + right[i][j] + down[i][j]) % MOD;
                    }

                    // Both states can move down
                    if (i + 1 < m) {
                        down[i + 1][j] =
                            (down[i + 1][j] + right[i][j] + down[i][j]) % MOD;
                    }
                }
            }
        }

        // Destination is empty, so both entry directions are valid
        return (right[m - 1][n - 1] + down[m - 1][n - 1]) % MOD;
    }
};
