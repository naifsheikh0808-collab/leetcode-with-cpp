class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at the previous position
        // whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> newDp(k, 0);

            int val = num % k;

            // Start a new subarray with nums[i]
            newDp[val]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int newRemainder = (r * val) % k;
                    newDp[newRemainder] += dp[r];
                }
            }

            dp = newDp;

            // Every subarray ending here is one valid operation
            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};