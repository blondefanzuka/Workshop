class Solution {
public:
    bool isValid(string s) {
stack <char> st;
	for (char ch : s) {
		if (ch == '(' || ch == '{' || ch == '[')
			st.push(ch);
		else {
		    if (st.empty())
		    return false;
		    else
			switch (ch) {
			case')': if (st.top() != '(') return false; break;
			case']': if (st.top() != '[') return false; break;
			case'}': if (st.top() != '{') return false; break;
			}
			st.pop();
		}
	}
 return st.empty();
    }
};
