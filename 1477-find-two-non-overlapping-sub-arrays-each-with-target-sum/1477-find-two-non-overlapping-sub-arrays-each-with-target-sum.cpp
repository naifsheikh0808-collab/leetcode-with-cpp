class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> best(n, INT_MAX); // best[i] = min length of a valid subarray ending at or before index i
        int ans = INT_MAX;
        int left = 0;
        long long sum = 0;
        
        for (int right = 0; right < n; right++) {
            sum += arr[right];
            while (sum > target) {
                sum -= arr[left];
                left++;
            }
            
            if (sum == target) {
                int curLen = right - left + 1;
                if (left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, best[left - 1] + curLen);
                }
                best[right] = curLen;
            }
            
            // propagate the minimum length found so far
            if (right > 0) {
                best[right] = min(best[right], best[right - 1]);
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};