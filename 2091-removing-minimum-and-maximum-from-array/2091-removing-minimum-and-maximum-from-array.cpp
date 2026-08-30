class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int mn = min_element(nums.begin(), nums.end()) - nums.begin();
        int mx = max_element(nums.begin(), nums.end()) - nums.begin();

        int left = min(mn, mx);
        int right = max(mn, mx);

        // 1. Remove both from the front
        int front = right + 1;

        // 2. Remove both from the back
        int back = n - left;

        // 3. Remove left one from front, right one from back
        int both = (left + 1) + (n - right);

        return min({front, back, both});
    }
};