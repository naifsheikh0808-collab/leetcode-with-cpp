class Solution {
public:
    set<string> parse(string &s, int &i) {
        set<string> result;

        while (i < s.size() && s[i] != '}') {

            set<string> current;

            if (s[i] == '{') {
                i++; // skip '{'

                current = parse(s, i);

                i++; // skip '}'
            }
            else {
                current.insert(string(1, s[i]));
                i++;
            }

            if (result.empty()) {
                result = current;
            }
            else {
                set<string> temp;

                for (string a : result) {
                    for (string b : current) {
                        temp.insert(a + b);
                    }
                }

                result = temp;
            }

            // If there is a comma, it means UNION.
            if (i < s.size() && s[i] == ',') {
                i++;

                set<string> next = parse(s, i);

                result.insert(next.begin(), next.end());
                break;
            }
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};