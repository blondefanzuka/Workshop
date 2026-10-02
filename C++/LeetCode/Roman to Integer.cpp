class Solution {
public:
    int romanToInt(string s) {
	vector <int> v;
	for (char ch : s) {
		switch (ch) {
		case 'I': v.push_back(1); break;
		case 'V': v.push_back(5); break;
		case 'X': v.push_back(10); break;
		case 'L': v.push_back(50); break;
		case 'C': v.push_back(100); break;
		case 'D': v.push_back(500); break;
		case 'M': v.push_back(1000); break;
		}
	}
	int ans = 0;
	if (v.size() > 1) {
        ans = v.back();
		if (v[0] >= v[1])
			ans += v[0];
		else ans -= v[0];
	}
	else ans += v[0];
	for (int i = 1; i < v.size() - 1; i++) {
		if (v[i] < v[i + 1])
			ans -= v[i];
		else ans += v[i];
	}
	return ans;
    }
};
