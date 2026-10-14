class Solution {
public:
    string reverseParentheses(string s) {
    string result;
	vector <int> ind;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			ind.push_back(result.length());
		}
		else if (s[i] == ')') {
			reverse(result.begin() + ind.back(), result.end());
			ind.pop_back();
		}
		else
			result += s[i];
	}
	return result;
    }
};
