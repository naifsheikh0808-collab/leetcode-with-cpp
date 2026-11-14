
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int ans = INT_MAX;

        vector<int> prefix(n + 1, 0);

        // Build prefix sum
        for(int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // Try every possible starting index
        for(int i = 0; i < n; i++) {

            // Try every valid subarray length
            for(int len = l; len <= r; len++) {

                int j = i + len;

                if(j > n) break;

                int sum = prefix[j] - prefix[i];

                if(sum > 0) {
                    ans = min(ans, sum);
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
