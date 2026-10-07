class Solution {
public:
    bool isValid(string s) {
        int count = 0;

        for (char c : s) {
            if (c == '(') {
                count++;
            }
            else if (c == ')') {
                count--;

                if (count < 0)
                    return false;
            }
        }

        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            string curr = q.front();
            q.pop();

            // If current string is valid
            if (isValid(curr)) {
                ans.push_back(curr);
                found = true;
            }

            // If we already found valid strings,
            // don't remove more characters.
            if (found)
                continue;

            // Generate strings by removing one parenthesis
            for (int i = 0; i < curr.size(); i++) {

                if (curr[i] != '(' && curr[i] != ')')
                    continue;

                string next = curr.substr(0, i) + curr.substr(i + 1);

                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};