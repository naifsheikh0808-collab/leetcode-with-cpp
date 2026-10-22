class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
       unordered_map<int, int> m;
        for(int i=0; i<nums.size(); i++){
            int first = nums[i];
            int second = first;
            if(m.find(second) != m.end()){
                if(abs(m[second] - i) <= k){
                    return true;
                }
            }
            m[first] = i;
        }
        return false;
    }
};