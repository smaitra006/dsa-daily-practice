// LeetCode questions on Graph
#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * PROBLEM 1: NUMBER OF PROVINCES (LeetCode 547)
 * ================================================================ */

/**
 * @brief Count the number of provinces (connected components) in a graph
 *
 * PROBLEM STATEMENT:
 * Given an `n x n` matrix `isConnected` representing an undirected graph
 * where `isConnected[i][j] == 1` means city `i` and city `j` are directly connected,
 * return the total number of provinces (groups of directly or indirectly connected cities).
 *
 * EXAMPLE:
 * Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
 * Output: 2
 *
 * APPROACH:
 * - Treat each city as a node in an undirected graph.
 * - A province is a connected component.
 * - Use DFS to explore all nodes in a component.
 * - Maintain a visited[] array to avoid revisiting nodes.
 * - For each unvisited node, start a DFS and count one province.
 *
 * @param isConnected 2D adjacency matrix representing connections
 * @return int Number of provinces (connected components)
 *
 * @complexity
 * Time: O(n^2) - Each cell in matrix may be visited once
 * Space: O(n)  - Visited array + recursion stack
 */

 class Solution {
    public:
        // DFS traversal to visit all cities in a province
        void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int node) {
            visited[node] = true;

            for (int neighbor = 0; neighbor < isConnected.size(); neighbor++) {
                if (isConnected[node][neighbor] == 1 && !visited[neighbor]) { // Extra condition cus its adj matrix
                    dfs(isConnected, visited, neighbor);
                }
            }
        }

        // Count number of connected components (provinces)
        int findCircleNum(vector<vector<int>>& isConnected) {
            int n = isConnected.size();
            vector<bool> visited(n, false);
            int provinces = 0;

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    dfs(isConnected, visited, node);
                    provinces++;
                }
            }

            return provinces;
        }
    };

/* ===================================================================
 * PROBLEM 200: NUMBER OF ISLANDS (LeetCode)
 * =================================================================== */

/**
 * @brief Count the number of islands in a 2D grid.
 *
 * PROBLEM STATEMENT:
 * Given a 2D grid of '1's (land) and '0's (water), return the number
 * of islands. An island is surrounded by water and is formed by connecting
 * adjacent lands horizontally or vertically.
 *
 * EXAMPLE:
 * Input:
 *   grid = [
 *     ['1','1','0','0','0'],
 *     ['1','1','0','0','0'],
 *     ['0','0','1','0','0'],
 *     ['0','0','0','1','1']
 *   ]
 * Output: 3
 *
 * APPROACH:
 * - Traverse the matrix.
 * - On finding an unvisited land cell ('1'), start DFS and mark all
 *   connected land as visited.
 * - Each DFS corresponds to one island.
 *
 * @param grid 2D grid of characters ('1' and '0')
 * @return int Number of islands
 *
 * @complexity
 * Time: O(m * n)
 * Space: O(m * n) for visited array and recursion stack
 */

 class Solution {
    public:
        void dfs(int i, int j, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
            int m = grid.size(), n = grid[0].size();
            if(i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || grid[i][j] == '0')
                return;

            visited[i][j] = true;

            // Visit all 4 directions (up, down, left, right)
            dfs(i+1, j, grid, visited);
            dfs(i-1, j, grid, visited);
            dfs(i, j+1, grid, visited);
            dfs(i, j-1, grid, visited);
        }

        int numIslands(vector<vector<char>>& grid) {
            int m = grid.size(), n = grid[0].size();
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            int islands = 0;

            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(grid[i][j] == '1' && !visited[i][j]) {
                        dfs(i, j, grid, visited);
                        islands++;
                    }
                }
            }

            return islands;
        }
    };

/* ===================================================================
 * PROBLEM 994: ROTTING ORANGES (LeetCode)
 * =================================================================== */

/**
 * @brief Find the minimum number of minutes to rot all oranges
 *
 * PROBLEM STATEMENT:
 * Given a 2D grid:
 * - 0 = empty cell
 * - 1 = fresh orange
 * - 2 = rotten orange
 * Each minute, any fresh orange adjacent (4-directionally) to a rotten orange
 * becomes rotten. Return the minimum number of minutes that must elapse until
 * no cell has a fresh orange. If impossible, return -1.
 *
 * EXAMPLE:
 * Input:
 *   grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 *
 * APPROACH:
 * - BFS traversal from all initially rotten oranges
 * - Each level of BFS represents a minute passed
 * - Count remaining fresh oranges; if any left at the end → return -1
 *
 * @param grid 2D grid of integers
 * @return int Minimum minutes to rot all oranges, or -1 if impossible
 *
 * @complexity
 * Time: O(m * n)
 * Space: O(m * n)
 */

 class Solution {
    public:
        int orangesRotting(vector<vector<int>>& grid) {
            int m = grid.size(), n = grid[0].size();
            queue<pair<int, int>> q;
            int fresh = 0;

            // Step 1: Count fresh oranges and enqueue all rotten ones
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(grid[i][j] == 2) {
                        q.push({i, j});
                    } else if(grid[i][j] == 1) {
                        fresh++;
                    }
                }
            }

            if(fresh == 0) return 0;

            int minutes = -1;
            vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

            // Step 2: BFS traversal
            while(!q.empty()) {
                int sz = q.size();
                minutes++;

                while(sz--) {
                    pair<int, int> curr = q.front(); q.pop();
                    int r = curr.first;
                    int c = curr.second;

                    for(int d = 0; d < 4; d++) {
                        int nr = r + directions[d].first;
                        int nc = c + directions[d].second;

                        if(nr >= 0 && nc >= 0 && nr < m && nc < n && grid[nr][nc] == 1) {
                            grid[nr][nc] = 2;
                            fresh--;
                            q.push({nr, nc});
                        }
                    }
                }
            }

            return (fresh == 0) ? minutes : -1;
        }
    };


/* ===================================================================
 * PROBLEM 733: FLOOD FILL (LeetCode)
 * =================================================================== */

/**
 * @brief Perform flood fill on a 2D image starting from (sr, sc)
 *
 * PROBLEM STATEMENT:
 * You are given an image (2D grid) where each pixel has an integer value.
 * A pixel is connected 4-directionally to its adjacent pixels.
 * Starting from pixel (sr, sc), change its color and all connected pixels
 * of the same original color to a new color.
 *
 * EXAMPLE:
 * Input:
 *   image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
 * Output:
 *   [[2,2,2],[2,2,0],[2,0,1]]
 *
 * APPROACH:
 * - Use DFS to visit all pixels connected to the start pixel that have the same color.
 * - Mark visited to avoid reprocessing.
 * - Change color during the traversal.
 *
 * @param image 2D grid of pixel values
 * @param sr Start row index
 * @param sc Start column index
 * @param color Target color to apply
 * @return Modified image after flood fill
 *
 * @complexity
 * Time: O(m * n) - in worst case all pixels are visited
 * Space: O(m * n) - visited array + recursion stack
 */

 class Solution {
    public:
        bool bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
            queue<pair<int, int>> q; // {node, parent}
            visited[start] = true;
            q.push({start, -1});

            while(!q.empty()) {
                pair<int, int> curr = q.front(); q.pop();
                int node = curr.first;
                int parent = curr.second;

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push({neighbor, node});
                    } else if (neighbor != parent) {
                        return true; // Cycle found
                    }
                }
            }

            return false;
        }

        bool hasCycle(int n, vector<vector<int>>& adj) {
            vector<bool> visited(n, false);

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    if (bfs(node, adj, visited)) return true;
                }
            }

            return false;
        }
    };

/* ===================================================================
 * PROBLEM 542: 01 MATRIX (LeetCode)
 * =================================================================== */

/**
 * @brief Return the distance of the nearest 0 for each cell in the matrix
 *
 * PROBLEM STATEMENT:
 * Given an `m x n` binary matrix `mat`, return a matrix where each cell
 * contains the distance to the nearest 0.
 * - Distance is calculated in terms of the number of steps (4-directional).
 *
 * EXAMPLE:
 * Input:
 *   mat = [[0,0,0],
 *          [0,1,0],
 *          [1,1,1]]
 * Output:
 *   [[0,0,0],
 *    [0,1,0],
 *    [1,2,1]]
 *
 * APPROACH:
 * - Use multi-source BFS from all 0s in the matrix.
 * - Initialize result matrix with -1.
 * - Start BFS from all cells with 0 and push their positions into queue.
 * - For each cell, update unvisited neighbors with distance +1.
 *
 * @param mat Input binary matrix
 * @return vector<vector<int>> Result matrix with distances to nearest 0
 *
 * @complexity
 * Time: O(m * n)
 * Space: O(m * n)
 */

 class Solution {
    public:
        vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
            int m = mat.size();
            int n = mat[0].size();

            queue<pair<int, int>> q;
            vector<vector<int>> result(m, vector<int>(n, -1));

            // Directions for 4-neighbor movement (up, down, left, right)
            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

            // Step 1: Enqueue all 0s and set their distance to 0
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(mat[i][j] == 0) {
                        result[i][j] = 0;
                        q.push({i, j});
                    }
                }
            }

            // Step 2: BFS to update distances for all 1s
            while(!q.empty()) {
                pair<int, int> cell = q.front(); q.pop();
                int i = cell.first;
                int j = cell.second;

                for(int d = 0; d < 4; d++) {
                    int new_i = i + directions[d].first;
                    int new_j = j + directions[d].second;

                    // If within bounds and not yet visited
                    if(new_i >= 0 && new_i < m && new_j >= 0 && new_j < n && result[new_i][new_j] == -1) {
                        result[new_i][new_j] = result[i][j] + 1;
                        q.push({new_i, new_j});
                    }
                }
            }

            return result;
        }
    };
