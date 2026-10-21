class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        if (is_sorted(s.begin(), s.end()))
            return 0;

        if (n == 2)
            return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // One operation is sufficient.
        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        // Three operations are needed only when the
        // first character is the unique maximum and
        // the last character is the unique minimum.
        if (s[0] == mx && s[n - 1] == mn) {
            int maxCount = count(s.begin(), s.end(), mx);
            int minCount = count(s.begin(), s.end(), mn);

            if (maxCount == 1 && minCount == 1)
                return 3;
        }

        return 2;
    }
};