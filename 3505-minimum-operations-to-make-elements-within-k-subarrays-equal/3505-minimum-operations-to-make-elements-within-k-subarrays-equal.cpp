
class Solution {
public:

    multiset<long long> low, high;
    long long sumLow = 0, sumHigh = 0;

    // Balance the two multisets
    void balance() {

        while (low.size() > high.size() + 1) {

            long long val = *low.rbegin();

            low.erase(prev(low.end()));
            sumLow -= val;

            high.insert(val);
            sumHigh += val;
        }

        while (low.size() < high.size()) {

            long long val = *high.begin();

            high.erase(high.begin());
            sumHigh -= val;

            low.insert(val);
            sumLow += val;
        }
    }

    // Insert an element
    void add(long long val) {

        if (low.empty() || val <= *low.rbegin()) {
            low.insert(val);
            sumLow += val;
        }
        else {
            high.insert(val);
            sumHigh += val;
        }

        balance();
    }

    // Remove an element
    void remove(long long val) {

        auto it = low.find(val);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= val;
        }
        else {
            it = high.find(val);
            high.erase(it);
            sumHigh -= val;
        }

        balance();
    }

    // Calculate minimum cost using median
    long long getCost() {

        long long median = *low.rbegin();

        long long leftCost =
            median * (long long)low.size() - sumLow;

        long long rightCost =
            sumHigh - median * (long long)high.size();

        return leftCost + rightCost;
    }

    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        vector<long long> cost(n - x + 1);

        // Step 1: Calculate cost of every window of size x
        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // Step 2: Dynamic Programming
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        // Base case: selecting zero windows costs zero
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        // Step 3: DP transitions
        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= k; j++) {

                // Option 1: Skip current element
                dp[i][j] = dp[i - 1][j];

                // Option 2: Select a window ending at i-1
                if (i >= x && dp[i - x][j - 1] != INF) {

                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
