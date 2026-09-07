class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;
        
        long long dp = 1;  // includes empty subsequence
        vector<long long> last(26, 0);

        for (char ch : s) {
            int c = ch - 'a';

            long long newDp = (2 * dp - last[c] + MOD) % MOD;

            last[c] = dp;
            dp = newDp;
        }

        // Remove empty subsequence
        return (dp - 1 + MOD) % MOD;
    }
};