class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n-1;
        int left_max = height[left], right_max= height[right];
        int water = 0;

        while(left < right){
            if(left_max < right_max){
                left++;
                left_max = max(left_max,height[left]);
                water += left_max - height[left];
            }
            else {
                right--;
                right_max = max(right_max,height[right]);
                water += right_max - height[right];
            }
        }
        return water;
    }
};