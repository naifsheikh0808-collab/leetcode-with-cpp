class Solution {
public:
    static const int MOD = 1e9 + 7;

    int numberOfSets(int n, int k) {
        vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));
        
        // dp[i][j] = ways to form j segments using points [0...i]
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }

        for (int j = 1; j <= k; j++) {
            long long sum = 0;

            for (int i = 1; i < n; i++) {
                // Start a new segment at some previous point
                sum = (sum + dp[i - 1][j - 1]) % MOD;

                // Don't necessarily use point i as an endpoint
                dp[i][j] = (dp[i - 1][j] + sum) % MOD;
            }
        }

        return dp[n - 1][k];
    }
};