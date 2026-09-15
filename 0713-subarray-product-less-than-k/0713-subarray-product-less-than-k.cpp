class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {

        int count = 0;
        int product = 1;
        int left = 0;
        
        if(k <= 1) return 0; //base case or edge case

        for(int right = 0; right<nums.size(); right++){
             product *= nums[right];
             while(product >= k){   //if condition but it doen't run only 1 time, instead it runs till satisfied.
                product /= nums[left];
                left++;
             }
             count+= right - left + 1;
        }
        return count;
    }
};