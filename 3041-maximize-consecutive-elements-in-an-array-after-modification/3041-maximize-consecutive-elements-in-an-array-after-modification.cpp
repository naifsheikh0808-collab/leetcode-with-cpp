
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        unordered_map<int, int> dp;
        int ans = 0;

        for (int x : nums) {

            // Save previous states BEFORE updating
            int prevX = dp[x];
            int prevXm1 = dp[x - 1];

            // Option 1: Use current element as x + 1
            dp[x + 1] = max(dp[x + 1], prevX + 1);

            // Option 2: Use current element as x
            dp[x] = max(dp[x], prevXm1 + 1);

            ans = max({ans, dp[x], dp[x + 1]});
        }

        return ans;
    }
};
