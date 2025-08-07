#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dfs(int r1, int c1, int r2, int n, vector<vector<int>>& grid)
    {
        int c2 = r1 + c1 - r2;
        if (r1 >= n || c1 >= n || r2 >= n || c2 >= n || grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return INT_MIN;

        if (r1 == n - 1 && c1 == n - 1)
            return grid[r1][c1];

        int curr = grid[r1][c1];
        if (r1 != r2 || c1 != c2)
            curr += grid[r2][c2];

        int a = dfs(r1 + 1, c1, r2 + 1, n, grid);
        int b = dfs(r1 + 1, c1, r2, n, grid);
        int c = dfs(r1, c1 + 1, r2 + 1, n, grid);
        int d = dfs(r1, c1 + 1, r2, n, grid);

        return curr + max({ a, b, c, d });
    }

    int maxCollectedFruits(vector<vector<int>>& fruits)
    {
        int n = fruits.size();
        return max(0, dfs(0, 0, 0, n, fruits));
    }
};

class Solution {
public:
    int dfs(int r1, int c1, int r2, int n, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp)
    {
        int c2 = r1 + c1 - r2;
        if (r1 >= n || c1 >= n || r2 >= n || c2 >= n || grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return INT_MIN;

        if (dp[r1][c1][r2] != -1)
            return dp[r1][c1][r2];

        if (r1 == n - 1 && c1 == n - 1)
            return grid[r1][c1];

        int curr = grid[r1][c1];
        if (r1 != r2 || c1 != c2)
            curr += grid[r2][c2];

        int a = dfs(r1 + 1, c1, r2 + 1, n, grid, dp);
        int b = dfs(r1 + 1, c1, r2, n, grid, dp);
        int c = dfs(r1, c1 + 1, r2 + 1, n, grid, dp);
        int d = dfs(r1, c1 + 1, r2, n, grid, dp);

        return dp[r1][c1][r2] = curr + max({ a, b, c, d });
    }

    int maxCollectedFruits(vector<vector<int>>& fruits)
    {
        int n = fruits.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, -1)));
        // return max(0, dfs(0, 0, 0, n, fruits));
    }
};

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& grid)
    {
        int n = grid.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        dp[n - 1][n - 1][n - 1] = grid[n - 1][n - 1];

        for (int r1 = n - 1; r1 >= 0; r1--) {
            for (int c1 = n - 1; c1 >= 0; c1--) {
                for (int r2 = n - 1; r2 >= 0; r2--) {
                    int c2 = r1 + c1 - r2;
                    if (c2 < 0 || c2 >= n) continue;

                    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;

                    int val = grid[r1][c1];
                    if (r1 != r2 || c1 != c2)
                        val += grid[r2][c2];

                    if (r1 + 1 < n && r2 + 1 < n)
                        dp[r1][c1][r2] = max(dp[r1][c1][r2], val + dp[r1 + 1][c1][r2 + 1]);
                    if (r1 + 1 < n && c2 + 1 < n)
                        dp[r1][c1][r2] = max(dp[r1][c1][r2], val + dp[r1 + 1][c1][r2]);
                    if (c1 + 1 < n && r2 + 1 < n)
                        dp[r1][c1][r2] = max(dp[r1][c1][r2], val + dp[r1][c1 + 1][r2 + 1]);
                    if (c1 + 1 < n && c2 + 1 < n)
                        dp[r1][c1][r2] = max(dp[r1][c1][r2], val + dp[r1][c1 + 1][r2]);
                }
            }
        }

        return max(0, dp[0][0][0]);
    }
};
