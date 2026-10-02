class Solution {
public:
    vector<string> ans;

    void generate(string s, int open, int close, int n) {

        // A valid combination is complete
        if (s.length() == 2 * n) {
            ans.push_back(s);
            return;
        }

        // We can add '(' if we haven't used all n opening brackets
        if (open < n) {
            generate(s + "(", open + 1, close, n);
        }

        // We can add ')' only when there is an unmatched '('
        if (close < open) {
            generate(s + ")", open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        generate("", 0, 0, n);
        return ans;
    }
};