
class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                open++;
            }
            else {
                // If the next character is ')',
                // consume it as a pair "))"
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                }
                else {
                    // Insert one ')' to make a pair
                    insertions++;
                }

                // Match the closing pair with an opening '('
                if (open > 0) {
                    open--;
                }
                else {
                    // Insert '(' because no opening exists
                    insertions++;
                }
            }
        }

        // Each remaining '(' needs two ')'
        insertions += open * 2;

        return insertions;
    }
};
