class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int painter = image[sr][sc];
        if (painter == color)
            return image;
        checker(image, sr, sc, color, painter);
        return image;
    }
    void checker(vector<vector<int>>& image, int sr, int sc, int color, int painter) {
        int rows = image.size();
        int cols = image[0].size();
        if (sr >= rows || sc >= cols || sr < 0 || sc < 0 || image[sr][sc] != painter)
            return;
        image[sr][sc] = color;
        checker(image, sr + 1, sc, color, painter);
        checker(image, sr - 1, sc, color, painter);
        checker(image, sr, sc + 1, color, painter);
        checker(image, sr, sc - 1, color, painter);
    }
};
