class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
       int left =0;
       int right = nums.size()-1;
       int position = nums.size()-1;
       vector<int> result(nums.size());
    
       while(left <= right){
        if(abs(nums[left]) > abs(nums[right])){
            result[position] = nums[left] * nums[left];
            left++;
       }
       else{
        result[position] = nums[right] * nums[right];
        right--;
       }
       position--;
       }

       return result;
    }
};