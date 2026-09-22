class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<int> s1;
        stack<int> t1;
        
        for(char c:s){              //loop iterate for each character in s string.
            if(c == '#'){           //if character is equal to # and
                if(!s1.empty()){    //stack s1 is not emppty then.
                    s1.pop();       //pop a character from stack s1.
                }
            }
            else{                   //else push that character in s1 stack.
                s1.push(c);
            }
        }
        
        for(char c:t){
            if(c == '#'){               // SAME AS ABOVE
                if(!t1.empty()){
                    t1.pop();
                }
            }
            else{
                t1.push(c);
            }
        }
        
        return s1 == t1;        //return TRUE/FALSE if equal.
    }
};