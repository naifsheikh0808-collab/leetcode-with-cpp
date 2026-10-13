
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> squares;

        for (int x : nums) {
            squares.push_back(1LL * x * x);
        }

        sort(squares.begin(), squares.end());

        long long score = 0;
        int n = squares.size();

        for (int i = 0; i < n; i++) {
            if (i < n / 2) {
                score -= squares[i];
            } else {
                score += squares[i];
            }
        }

        return score;
    }
};
