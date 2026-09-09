class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        // Start of each block: 1, 1000, 1000000, ...
        long long start = 1;
        long long commas = 0;

        while (start <= n) {
            long long end = min(n, start * 1000 - 1);

            // Numbers in [start, end] have 'commas' commas.
            ans += (end - start + 1) * commas;

            start *= 1000;
            commas++;
        }

        return ans;
    }
};