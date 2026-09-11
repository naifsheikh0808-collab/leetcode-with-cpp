class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> freq(10, 0);

        // Count how many times each digit appears.
        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

        // Every 3-digit even number.
        for (int num = 100; num <= 998; num += 2) {
            int x = num;
            vector<int> need(10, 0);

            // Extract its three digits.
            need[x % 10]++;
            x /= 10;

            need[x % 10]++;
            x /= 10;

            need[x % 10]++;

            // Check if we have enough copies of every digit.
            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (need[d] > freq[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                ans++;
            }
        }

        return ans;
    }
};