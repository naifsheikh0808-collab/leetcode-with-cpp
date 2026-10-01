class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s) {

            // Opening bracket
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            }

            // Closing bracket
            else {
                if (st.empty()) {
                    return false;
                }

                char top = st.top();

                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }

                st.pop();
            }
        }

        return st.empty();
    }
};