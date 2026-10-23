
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n = nums.size();
        int k = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                if (k == -1)
                    k = nums[i];
                else
                    k &= nums[i];
            }
        }

        return k == -1 ? 0 : k;
    }
};
