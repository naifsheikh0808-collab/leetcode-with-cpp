class Solution {
public:
    bool checkString(string s) {
        int n = s.size();
        int left = 0;
        int right = n-1;
        while(left < right){
            if(s[left]=='a' && s[right]=='b'){
                left++;
                right--;
            }
            else if(s[left]=='a'){
                left++;
            }
            else if(s[right]=='b'){
                right--;
            }
            else{
                return false;
            }
        }
        return true;
    }
};