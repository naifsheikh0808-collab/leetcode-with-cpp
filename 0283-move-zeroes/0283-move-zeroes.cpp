class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;   
        for(int i=0; i<nums.size(); i++){
            if(nums[i] != 0){
                swap(nums[i], nums[j]);
                j++;
            }
        }
    }
};

// - i traverses the entire array.
// - j points to the position where the next non-zero element should go.
// - Whenever nums[i] != 0, swap nums[i] with nums[j], then increment j.
// - Zeroes naturally move toward the end.