class Solution {
public:
    bool alphanumeric(char c){
        return (c >= 'A' && c <= 'Z') ||
                (c >= 'a' && c <= 'z') ||
                (c >= '0' && c <= '9');
    }
    bool isPalindrome(string s) {
        int i = 0;
        int j = s.size()-1;

        while (i <= j){
            char c1 = s[i];
            char c2 = s[j];

                     
            if(!alphanumeric(c1)){
                i++;
                continue;
            }

            if(!alphanumeric(c2)){
                j--;
                continue;
            }

            i++;
            j--;

            if(tolower(c1) != tolower(c2)){
                return false;
            }
        }
        
        return true;
    }
};