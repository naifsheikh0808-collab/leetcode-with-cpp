
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        // cost[l][r] = minimum changes needed
        // to make s[l...r] a semi-palindrome.
        vector<vector<int>> cost(n, vector<int>(n, 0));

        // Precompute semi-palindrome costs
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len <= n; l++) {

                int r = l + len - 1;
                cost[l][r] = INT_MAX;

                // Try every proper divisor of len
                for (int d = 1; d < len; d++) {

                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Compare characters in each group
                    for (int i = 0; i < d; i++) {

                        int left = l + i;
                        int right = r - ((len - 1 - i) % d);

                        while (left < right) {
                            if (s[left] != s[right])
                                changes++;

                            left += d;
                            right -= d;
                        }
                    }

                    cost[l][r] = min(cost[l][r], changes);
                }
            }
        }

        // dp[i][j] = minimum changes to divide
        // first i characters into j substrings.
        vector<vector<int>> dp(n + 1,
                               vector<int>(k + 1, INT_MAX));

        dp[0][0] = 0;

        for (int j = 1; j <= k; j++) {
            for (int i = 2 * j; i <= n; i++) {

                // Last substring is s[p...i-1]
                for (int p = 2 * (j - 1);
                     p <= i - 2; p++) {

                    if (dp[p][j - 1] == INT_MAX)
                        continue;

                    dp[i][j] = min(
                        dp[i][j],
                        dp[p][j - 1] + cost[p][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
