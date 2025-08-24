#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Path With Minimum Effort (LeetCode 1631)
//
// Task:
// You are given a 2D grid `heights` where heights[r][c] represents the height
// of a cell. A path’s "effort" is defined as the maximum absolute difference
// in heights between consecutive cells along the path.
//
// Find a path from the top-left corner (0,0) to the bottom-right corner (m-1,n-1)
// that minimizes this effort, and return the minimum effort required.
//
// Approach (Dijkstra’s Algorithm for Grids):
// - Each cell is treated as a graph node.
// - Use a min-heap (priority_queue with greater) to process the cell with the
//   current minimum effort.
// - Relax neighbors: new effort = max(current effort, abs(height diff)).
// - If this new effort is smaller than the previously recorded effort, update it
//   and push the neighbor into the heap.
// - Stop when the bottom-right cell is popped (guaranteed minimum effort).
//
// Complexity:
// - Time: O(M * N * log(M*N)) → Each cell can be inserted into heap, log factor
//   due to priority queue.
// - Space: O(M * N) for effort grid and heap storage.
//==============================================================================

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        int m = heights.size();
        int n = heights[0].size();

        // Min-heap: {effort, {row, col}}
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > pq;

        // Track minimum effort to reach each cell
        vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
        vector<pair<int, int>> directions = { {0,1}, {1,0}, {0,-1}, {-1,0} };

        // Start from (0,0)
        effort[0][0] = 0;
        pq.push({ 0, {0,0} });

        while (!pq.empty()) {
            auto [currEffort, cell] = pq.top();
            auto [r, c] = cell;
            pq.pop();

            // If reached destination, return effort
            if (r == m - 1 && c == n - 1)
                return currEffort;

            // Explore 4 directions
            for (auto dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int newEffort = max(currEffort, abs(heights[nr][nc] - heights[r][c]));

                    // Relaxation step
                    if (newEffort < effort[nr][nc]) {
                        effort[nr][nc] = newEffort;
                        pq.push({ newEffort, {nr, nc} });
                    }
                }
            }
        }

        return effort[m - 1][n - 1]; // Fallback (should never reach here)
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     vector<vector<int>> heights = {{1,2,2}, {3,8,2}, {5,3,5}};
//
//     cout << sol.minimumEffortPath(heights) << endl;
//     // Expected Output: 2
// }
//
// Explanation:
// Path: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)
// Efforts: |1-2|=1, |2-2|=0, |2-2|=0, |2-5|=3 → max = 3
// But optimal path minimizes to 2.
//==============================================================================
