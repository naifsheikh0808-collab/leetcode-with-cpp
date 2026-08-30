class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        
        int left = 0;
        int right = left +1;
        while(right <= nums.size()-1){
            if(nums[left]==nums[right]){
                right++;
            }
            else{
                left++;
                nums[left] = nums[right];
                right++;
            }
        }
        //number of unique element
        return(left+1);

    }
};