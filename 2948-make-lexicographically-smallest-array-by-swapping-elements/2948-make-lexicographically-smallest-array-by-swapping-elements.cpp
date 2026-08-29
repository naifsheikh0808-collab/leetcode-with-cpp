class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());

        vector<int> ans(n);
        int i = 0;

        while (i < n) {
            int j = i;

            // Elements belong to the same connected group
            // if consecutive sorted values differ by <= limit.
            while (j + 1 < n && a[j + 1].first - a[j].first <= limit)
                j++;

            vector<int> indices;
            vector<int> values;

            for (int k = i; k <= j; k++) {
                values.push_back(a[k].first);
                indices.push_back(a[k].second);
            }

            sort(indices.begin(), indices.end());

            for (int k = 0; k < indices.size(); k++)
                ans[indices[k]] = values[k];

            i = j + 1;
        }

        return ans;
    }
};