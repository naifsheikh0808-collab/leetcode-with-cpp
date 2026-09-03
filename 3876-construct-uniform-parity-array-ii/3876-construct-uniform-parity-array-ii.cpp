class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // If the minimum is odd, we can make everything odd:
        // - odd numbers stay unchanged
        // - even numbers subtract the minimum odd number
        if (mn & 1)
            return true;

        // If the minimum is even, we can only make everything even
        // if every element is already even.
        for (int x : nums1) {
            if (x & 1)
                return false;
        }

        return true;
    }
};