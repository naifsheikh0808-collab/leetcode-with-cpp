class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;
            int prevMax = -1;

            for (int start = 0; start < n; start += k) {
                int end = start + k;
                int drops = 0;

                for (int i = start; i < end; i++) {
                    int next = (i + 1 == end) ? start : i + 1;
                    if (nums[i] > nums[next]) {
                        drops++;
                    }
                }

                if (drops > 1) {
                    valid = false;
                    break;
                }

                // Find the minimum and maximum of this block.
                int mn = nums[start], mx = nums[start];

                for (int i = start + 1; i < end; i++) {
                    mn = min(mn, nums[i]);
                    mx = max(mx, nums[i]);
                }

                // The sorted blocks must also be globally ordered.
                if (start > 0 && prevMax > mn) {
                    valid = false;
                    break;
                }

                prevMax = mx;
            }

            if (valid) ans += k;
        }

        return ans;
    }
};