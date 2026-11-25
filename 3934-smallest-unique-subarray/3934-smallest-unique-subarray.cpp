class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
                int n = nums.size();

        // Step 1: Build Suffix Array
        vector<int> sa(n), rank(n), newRank(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = nums[i];
        }

        for (int k = 1; k < n; k *= 2) {

            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int ra = (a + k < n) ? rank[a + k] : -1;
                int rb = (b + k < n) ? rank[b + k] : -1;

                return ra < rb;
            });

            newRank[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                int a1 = rank[a];
                int b1 = rank[b];

                int a2 = (a + k < n) ? rank[a + k] : -1;
                int b2 = (b + k < n) ? rank[b + k] : -1;

                newRank[b] = newRank[a] +
                    (a1 != b1 || a2 != b2);
            }

            rank = newRank;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        // Step 2: Build LCP Array using Kasai's Algorithm
        vector<int> pos(n), lcp(n, 0);

        for (int i = 0; i < n; i++) {
            pos[sa[i]] = i;
        }

        int h = 0;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            if (p == 0) continue;

            int j = sa[p - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[p] = h;

            if (h > 0) h--;
        }

        // Step 3: Find the minimum unique subarray length
        int ans = n;

        for (int p = 0; p < n; p++) {

            int common = 0;

            // LCP with previous suffix
            if (p > 0)
                common = max(common, lcp[p]);

            // LCP with next suffix
            if (p + 1 < n)
                common = max(common, lcp[p + 1]);

            int requiredLength = common + 1;

            if (requiredLength <= n - sa[p]) {
                ans = min(ans, requiredLength);
            }
        }

        return ans;
    }
};