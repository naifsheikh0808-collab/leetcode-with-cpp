class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
       int slow = 0; 
       int fast = 0;
       
       while(fast < nums.size()){
            if(slow < 2 || nums[fast]!=nums[slow-2]){
              nums[slow] = nums[fast];
              slow++;
            }
        fast++;
       } 
       return slow;
    }
};