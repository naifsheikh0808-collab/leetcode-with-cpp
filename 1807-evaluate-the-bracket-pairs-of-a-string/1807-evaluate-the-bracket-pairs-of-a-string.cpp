class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto &item : knowledge) {
            mp[item[0]] = item[1];
        }

        string ans;

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '(') {
                string key = "";

                i++;  // move inside the bracket

                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Check if key exists
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }
            }
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};