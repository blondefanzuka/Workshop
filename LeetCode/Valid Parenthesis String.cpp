class Solution {
public:
    bool checkValidString(string s) {
        stack <int> stBracket;
        stack <int> stSpecial;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stBracket.push(i);
            }
            else if (s[i] == '*') {
                stSpecial.push(i);
            }
            else {
                if (!stBracket.empty())
                    stBracket.pop();
                else
                    if (!stSpecial.empty()) {
                        stSpecial.pop();
                    }
                    else
                        return false;
            }
        }
        while (!stBracket.empty() && !stSpecial.empty()) {
            if (stBracket.top() > stSpecial.top())
                return false;
            else {
                stBracket.pop();
                stSpecial.pop();
            }
        }
        return stBracket.empty();
    }
};
