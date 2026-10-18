
class Solution {
public:
    const int MOD = 1e9 + 7;
    vector<vector<long long>> comb;

    long long solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2) return 1;

        vector<int> left, right;

        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[0])
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long waysLeft = solve(left);
        long long waysRight = solve(right);

        long long ways = comb[n - 1][left.size()];

        ways = (ways * waysLeft) % MOD;
        ways = (ways * waysRight) % MOD;

        return ways;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        // Precompute combinations using Pascal's Triangle
        comb.assign(n + 1, vector<long long>(n + 1, 0));

        for (int i = 0; i <= n; i++) {
            comb[i][0] = comb[i][i] = 1;

            for (int j = 1; j < i; j++) {
                comb[i][j] =
                    (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }

        // Subtract the original ordering
        return (solve(nums) - 1 + MOD) % MOD;
    }
};
