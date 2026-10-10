
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        vector<int> diff(n);

        long long k = 1LL * k1 + k2;
        long long total = 0;
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            maxDiff = max(maxDiff, diff[i]);
        }

        // Enough operations to make all differences zero
        if (k >= total) return 0;

        // Binary search for the minimum achievable level
        int low = 0, high = maxDiff;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid) {
                    needed += d - mid;
                }
            }

            if (needed <= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        int level = low;
        long long used = 0;
        long long ans = 0;
        long long count = 0;

        for (int d : diff) {
            if (d > level) {
                used += d - level;
                ans += 1LL * level * level;
                count++;
            } else {
                ans += 1LL * d * d;
                if (d == level) count++;
            }
        }

        // Use leftover operations to reduce level to level - 1
        long long remaining = k - used;
        ans -= remaining * (2LL * level - 1);

        return ans;
    }
};
