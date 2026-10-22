class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int pos = find(nums.begin(), nums.end(), 0) - nums.begin();
        int ans = INT_MAX;

        // Case 1: Rotate the original array left by k.
        int k = pos;
        bool ok = true;

        for (int i = 0; i < n; i++) {
            if (nums[(i + k) % n] != i) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = min(ans, min(k, n - k + 2));
        }

        // Case 2: Reverse first, then rotate left by k.
        k = n - 1 - pos;
        ok = true;

        for (int i = 0; i < n; i++) {
            if (nums[n - 1 - ((i + k) % n)] != i) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = min(ans, min(k + 1, n - k + 1));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};