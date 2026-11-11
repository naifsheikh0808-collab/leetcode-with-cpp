
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long costA = (long long)need1 * cost1
                        + (long long)need2 * cost2;

        long long costB = (long long)max(need1, need2) * costBoth;

        long long common = min(need1, need2);

        long long costC = common * costBoth
                        + (long long)(need1 - common) * cost1
                        + (long long)(need2 - common) * cost2;

        return min({costA, costB, costC});
    }
};
