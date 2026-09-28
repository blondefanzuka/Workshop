class Solution {
public:
    int maxDepth(string s) {
        int count = 0, answer = 0;
        for (int i = 0; i < s.size(); i++){
            if (s[i] == '('){
                count++;
            }
            else if (s[i] == ')'){
                count--;
            }
            answer = max(count,answer);
        }
    return answer;
    }
};
