
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 32 - __builtin_clz(n);

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Find next strictly greater element
        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            if (!st.empty()) {
                nxt[i] = st.top();
            }

            st.push(i);
        }

        // Binary lifting tables
        vector<vector<int>> up(LOG, vector<int>(n, n));
        vector<vector<long long>> sum(LOG, vector<long long>(n, 0));

        // First jump
        for (int i = 0; i < n; i++) {
            int j = nxt[i];

            if (j < n) {
                up[0][i] = j;

                sum[0][i] =
                    1LL * nums[i] * (j - i)
                    - (pref[j] - pref[i]);
            }
        }

        // Build binary lifting tables
        for (int p = 1; p < LOG; p++) {
            for (int i = 0; i < n; i++) {
                int mid = up[p - 1][i];

                if (mid < n && up[p - 1][mid] < n) {
                    up[p][i] = up[p - 1][mid];

                    sum[p][i] =
                        sum[p - 1][i] + sum[p - 1][mid];
                }
            }
        }

        // Calculate minimum operations for [l, r]
        auto getCost = [&](int l, int r) -> long long {
            int pos = l;
            long long cost = 0;

            for (int p = LOG - 1; p >= 0; p--) {
                int next = up[p][pos];

                if (next <= r) {
                    cost += sum[p][pos];
                    pos = next;
                }
            }

            // Remaining segment
            cost += 1LL * nums[pos] * (r - pos + 1)
                    - (pref[r + 1] - pref[pos]);

            return cost;
        };

        // Binary search for the smallest valid left
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int lo = 0, hi = r;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (getCost(mid, r) <= k) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }

            ans += (r - lo + 1);
        }

        return ans;
    }
};
