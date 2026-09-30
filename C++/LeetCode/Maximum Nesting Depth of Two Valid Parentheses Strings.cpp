class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {

        int k = 0, maxdepth = 0;
        vector<int> answer;

        for (int i = 0; i < seq.size(); i++) {
            if (seq[i] == '(') {
                k++;
                maxdepth = max(maxdepth, k);
            }
            else if (seq[i] == ')') k--;
        }

        int newdepth = (maxdepth / 2) + (maxdepth % 2);
        k = 0;

        for (char ch : seq) {
            if (ch == '(') {
                k++;
                if (k <= newdepth)
                    answer.push_back(0);
                else
                    answer.push_back(1);
            }
            else {
                if (k <= newdepth)
                    answer.push_back(0);
                else
                    answer.push_back(1);
                k--;
            }
        }
        return answer;
    }
};
