class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        vector<vector<string>> ans;
        // 1. iterate each word in the string and store in the temp string.
        // 2.  ex: s = eat then temp = eat
        // 3. sort the string [eat -> aet] and
        // 4. make key of it m[aet] in the map and push the temp string ("eat") into key's value; (aet -> eat); (value is vector)
        // (aet -> eat, ate, tea)
        
        for(auto s : strs){
            string temp = s;             // ex: s = eat then temp = eat
            sort(s.begin(), s.end());   // sort the string [eat -> aet] and
            m[s].push_back(temp);      //push in the vector; m[s] is a vector value
        }

        //storing the value (which is vectors) of map in the ans vector;
        for(auto x : m){
            ans.push_back(x.second);
        }
        return ans;
        

    }
};