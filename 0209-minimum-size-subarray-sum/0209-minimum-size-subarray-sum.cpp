class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int ans_length = INT_MAX;
        int sum = 0;
        int left = 0;
        
        for(int right = 0; right<nums.size(); right++){
            sum += nums[right];
            while(sum >= target){
                int current_length = right-left+1;
                ans_length = min(ans_length,current_length);
                sum -= nums[left];
                left++;
            }
        }

        if(ans_length == INT_MAX){
            return 0;
        }else{
            return ans_length;
        }
    }
};