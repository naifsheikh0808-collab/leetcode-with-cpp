class Solution {
public:
    int maxArea(vector<int>& height) {
        
        int n = height.size();
        int left = 0; 
        int right = n-1;
        int max_area = 0;

        while(left <= right){
            
            int h = min(height[left],height[right]);    //choose min height from 2 indices.
            int width = right - left;                   //find widht from indices
            int area = h*width;                         //find area
            max_area = max(max_area, area);             //compare with max Area & update
            if(height[left] <= height[right]) left++;   //increment the iterator accordingly
            else right--;

        }
        return max_area;                            //return the max_area.

    }
};