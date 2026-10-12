
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        vector<int> bits(31, 0);

        // Count how many numbers contain each bit
        for (int num : nums) {
            for (int b = 0; b < 31; b++) {
                if (num & (1 << b)) {
                    bits[b]++;
                }
            }
        }

        long long ans = 0;

        // Construct k maximum possible numbers
        for (int i = 0; i < k; i++) {
            long long x = 0;

            for (int b = 0; b < 31; b++) {
                if (bits[b] > 0) {
                    x |= (1LL << b);
                    bits[b]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return ans;
    }
};
