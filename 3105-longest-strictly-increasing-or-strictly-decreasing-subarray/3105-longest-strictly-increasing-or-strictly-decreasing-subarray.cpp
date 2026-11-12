class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        int max_len=1;
        int increase = 1;   //increaseing array size
        int decrease = 1;   //decreaseing array size

        for(int i=1; i<n; i++){             //start with index 1
            if(nums[i]>nums[i-1]){
                increase++;      //if incre subarray found, update the size of decre
                decrease=1;      // and reset the count of decre_subarray_size
            }
            else if(nums[i]<nums[i-1]){
                decrease++;         //if decre subarray found, update the size of decre
                increase=1;         //and reset the size of incre
            }
            else{   //nums[i] == nums[i-1]
                decrease=1;         //if equal element found reset both subarray size
                increase=1;
                continue;
            }
            //compare & update longest subarray till now.
            max_len = max(max_len,max(increase,decrease));   
        }
        
        return max_len;
    }
};