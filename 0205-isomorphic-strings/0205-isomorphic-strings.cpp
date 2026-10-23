class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char,char> m1;
        unordered_map<char,char> m2;
        if(s.size() != t.size()){
            return false;
        }
        for(int i=0; i<s.size(); i++){
            char a = s[i];
            char b = t[i];
            if(m1.count(a) && m1[a] != b){
                return false;
            }
              if(m2.count(b) && m2[b] != a){
                return false;
            }
            m1[a] = b;
            m2[b] = a;
        }
        return true;
    }
};