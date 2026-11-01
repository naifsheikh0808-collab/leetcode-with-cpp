class Solution {
public:
    bool isPalindrome(int x) {
       
       if(x < 0) return false;                  //if -ve number

       long long reverseNumber = 0;
       int temp = x;
       while(temp > 0){
        int last_digit = temp % 10;                         //access the last digit
        reverseNumber = reverseNumber * 10 + last_digit;    //append the last digit in reverseNumber
        temp /= 10;                                         //update the original nunber store in temp.
       }

       return x == reverseNumber;                       //compare the OG & reverse number
    }
};