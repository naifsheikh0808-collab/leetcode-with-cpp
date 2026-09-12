class Solution {
public:
    struct State {
        long long score;
        vector<int> ids;

        State(long long s = 0, vector<int> v = {})
            : score(s), ids(v) {}
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return lexicographical_compare(
            a.ids.begin(), a.ids.end(),
            b.ids.begin(), b.ids.end()
        );
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];

            return x[0] < y[0];
        });

        // Store all right endpoints
        vector<long long> right(n);

        for (int i = 0; i < n; i++)
            right[i] = a[i][1];

        /*
            prev[i] = number of intervals before i
                      whose right < a[i].left

            Because intervals sharing a boundary overlap,
            we need STRICTLY:
                right < left
        */
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            prev[i] = lower_bound(
                right.begin(),
                right.begin() + i,
                a[i][0]
            ) - right.begin();
        }

        /*
            dp[i][k] =
            best result using first i intervals,
            choosing at most k intervals.
        */
        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; i++) {

            // Don't take current interval
            for (int k = 0; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
            }

            // Take current interval
            for (int k = 1; k <= 4; k++) {

                State candidate = dp[prev[i - 1]][k - 1];

                candidate.score += a[i - 1][2];

                int originalIndex = a[i - 1][3];

                // Insert index in sorted order
                auto pos = lower_bound(
                    candidate.ids.begin(),
                    candidate.ids.end(),
                    originalIndex
                );

                candidate.ids.insert(pos, originalIndex);

                if (better(candidate, dp[i][k])) {
                    dp[i][k] = candidate;
                }
            }
        }

        return dp[n][4].ids;
    }
};
