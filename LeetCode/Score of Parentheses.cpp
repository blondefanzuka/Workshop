class Solution {
public:
    int scoreOfParentheses(string s) {
        stack <int> st;
        int ans = 0;
        for (int i = 0; i < s.size(); i++){
            if (s[i] == '('){
                st.push(i);
            }
            else{
                if ((st.top() + 1) == i)
                ans += pow(2,st.size()-1);
                st.pop();
            }
        }
        return ans;
    }
};
