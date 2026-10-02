class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int islands = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    isMore(grid, i, j);
                }
            }
        }
        return islands;
    }

        void isMore(vector<vector<char>>& grid, int i, int j) {
        int rows = grid.size();
        int cols = grid[0].size();
        if (i >= rows || j >= cols || i < 0 || j < 0 || grid[i][j] == '0')
            return;

        grid[i][j] = '0';
        isMore(grid, i - 1, j);
        isMore(grid, i + 1, j);
        isMore(grid, i, j + 1);
        isMore(grid, i, j - 1);
    }
};
