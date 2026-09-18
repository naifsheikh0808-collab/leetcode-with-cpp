class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int low = 0;
        int high = nums.size()-1;
        //finding starting and ending of the sub-array
        while(low + 1 < nums.size() && nums[low] <= nums[low+1]) low++;
        while(high - 1 >= 0 && nums[high-1] <= nums[high]) high --;

        //if low reaches end of array successfully it means array is sorted
        //then return 0 length of sub array.
        if (low == nums.size()-1) return 0;

        int wMin = INT_MAX; //largest no. store for comparision
        int wMax = INT_MIN; //smallest no. store for comparision

        for(int i = low; i <= high; i++){
            wMin = min(wMin,nums[i]);  //store Smallest number from unsorted window.
            wMax = max(wMax,nums[i]);  //store Largest number from unsorted window.
        }

        //expanding the window if outside element is greater than smallest element from the window.
        while(low - 1 >=0 && nums[low-1] > wMin) low--;
        //expanding the window if outside element is lesser than smallest element from the window.
        while(high + 1 < nums.size() && nums[high + 1] < wMax) high++;

        //return the size of the array window.
        return high - low + 1;
    }
};