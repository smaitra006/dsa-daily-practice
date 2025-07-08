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

/* ===================================================================
 * PROBLEM 130: SURROUNDED REGIONS (LeetCode)
 * =================================================================== */

/**
 * @brief Capture all regions surrounded by 'X'
 *
 * PROBLEM STATEMENT:
 * Given an `m x n` board containing 'X' and 'O', capture all regions that are
 * 4-directionally surrounded by 'X'. Flip all surrounded 'O' into 'X'.
 *
 * Any 'O' connected to a boundary 'O' should **not** be flipped.
 *
 * EXAMPLE:
 * Input:
 *   board = [["X","X","X","X"],
 *            ["X","O","O","X"],
 *            ["X","X","O","X"],
 *            ["X","O","X","X"]]
 * Output:
 *   [["X","X","X","X"],
 *    ["X","X","X","X"],
 *    ["X","X","X","X"],
 *    ["X","O","X","X"]]
 *
 * APPROACH:
 * - Start DFS from all boundary 'O's to mark them as safe.
 * - Then flip all unvisited 'O's (surrounded) to 'X'.
 *
 * @complexity
 * Time: O(m * n)
 * Space: O(m * n) for visited array + recursion stack
 */

 class Solution {
    public:
        void dfs(vector<vector<char>>& board, int sr, int sc, vector<vector<bool>>& visited) {
            int m = board.size();
            int n = board[0].size();

            // Out of bounds or already visited or not an 'O'
            if(sr < 0 || sr >= m || sc < 0 || sc >= n || visited[sr][sc] || board[sr][sc] == 'X')
                return;

            visited[sr][sc] = true;

            // Directions: up, down, left, right
            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for(auto dir : directions) {
                int new_sr = sr + dir.first;
                int new_sc = sc + dir.second;
                dfs(board, new_sr, new_sc, visited);
            }
        }

        void solve(vector<vector<char>>& board) {
            int m = board.size();
            if(m == 0) return;
            int n = board[0].size();
            vector<vector<bool>> visited(m, vector<bool>(n, false));

            // 1. Start DFS from all boundary 'O's to mark safe regions

            // Top & Bottom row
            for(int j = 0; j < n; j++) {
                if(board[0][j] == 'O' && !visited[0][j]) {
                    dfs(board, 0, j, visited);
                }
                if(board[m - 1][j] == 'O' && !visited[m - 1][j]) {
                    dfs(board, m - 1, j, visited);
                }
            }

            // Left & Right column
            for(int i = 0; i < m; i++) {
                if(board[i][0] == 'O' && !visited[i][0]) {
                    dfs(board, i, 0, visited);
                }
                if(board[i][n - 1] == 'O' && !visited[i][n - 1]) {
                    dfs(board, i, n - 1, visited);
                }
            }

            // 2. Flip all unvisited 'O's to 'X'
            for(int i = 1; i < m - 1; i++) {
                for(int j = 1; j < n - 1; j++) {
                    if(board[i][j] == 'O' && !visited[i][j]) {
                        board[i][j] = 'X';
                    }
                }
            }
        }
    };

/* ===================================================================
 * PROBLEM 1020: NUMBER OF ENCLAVES (LeetCode) MULTI-SOURCE DFS
 * =================================================================== */

/**
 * @brief Count land cells (1s) that cannot reach the boundary
 *
 * PROBLEM STATEMENT:
 * You are given an `m x n` binary matrix `grid`, where `0` represents sea and `1` represents land.
 * A land cell is considered **enclave** if it cannot reach any boundary of the matrix.
 * Return the number of enclave cells.
 *
 * EXAMPLE:
 * Input:
 *   grid = [[0,0,0,0],
 *           [1,0,1,0],
 *           [0,1,1,0],
 *           [0,0,0,0]]
 * Output: 3
 *
 * APPROACH:
 * - Perform DFS from boundary land cells (1s) to mark them as visited.
 * - Remaining unvisited 1s inside are enclave cells.
 *
 * @complexity
 * Time: O(m * n)
 * Space: O(m * n) for visited + recursion stack
 */

 class Solution {
    public:
        void dfs(vector<vector<int>>& grid, int sr, int sc, vector<vector<bool>>& visited) {
            int m = grid.size();
            int n = grid[0].size();

            if (sr < 0 || sr >= m || sc < 0 || sc >= n || visited[sr][sc] || grid[sr][sc] == 0)
                return;

            visited[sr][sc] = true;

            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto dir : directions) {
                int new_sr = sr + dir.first;
                int new_sc = sc + dir.second;
                dfs(grid, new_sr, new_sc, visited);
            }
        }

        int numEnclaves(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
            vector<vector<bool>> visited(m, vector<bool>(n, false));

            // Step 1: Run DFS for all boundary cells having 1
            // Top and Bottom row
            for (int j = 0; j < n; j++) {
                if (grid[0][j] == 1 && !visited[0][j]) {
                    dfs(grid, 0, j, visited);
                }
                if (grid[m - 1][j] == 1 && !visited[m - 1][j]) {
                    dfs(grid, m - 1, j, visited);
                }
            }

            // Left and Right column
            for (int i = 0; i < m; i++) {
                if (grid[i][0] == 1 && !visited[i][0]) {
                    dfs(grid, i, 0, visited);
                }
                if (grid[i][n - 1] == 1 && !visited[i][n - 1]) {
                    dfs(grid, i, n - 1, visited);
                }
            }

            // Step 2: Count the unvisited land cells (enclaves)
            int result = 0;
            for (int i = 1; i < m - 1; i++) {
                for (int j = 1; j < n - 1; j++) {
                    if (grid[i][j] == 1 && !visited[i][j]) {
                        result++;
                    }
                }
            }

            return result;
        }
    };

/* ===================================================================
 * PROBLEM 1020: NUMBER OF ENCLAVES (LeetCode) MULTI-SOURCE BFS
 * =================================================================== */

/**
 * @brief Count number of land cells that cannot reach the boundary using BFS
 *
 * PROBLEM STATEMENT:
 * You are given an `m x n` binary matrix `grid`, where:
 * - `0` represents sea, and
 * - `1` represents land.
 *
 * A land cell is an **enclave** if it cannot reach any boundary cell
 * (any cell on the edge of the grid) by moving 4-directionally through land.
 * Return the total count of enclave land cells.
 *
 * APPROACH:
 * - Use **Multi-source BFS** starting from all boundary land cells (1s).
 * - Mark all reachable land cells as visited.
 * - Count the remaining unvisited land cells as enclaves.
 *
 * @complexity
 * Time: O(m * n)
 * Space: O(m * n) for visited and queue
 */

 class Solution {
    public:
        int numEnclaves(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();

            vector<vector<bool>> visited(m, vector<bool>(n, false));
            queue<pair<int, int>> q;

            // Step 1: Add all boundary land cells to the queue
            for (int j = 0; j < n; j++) {
                if (grid[0][j] == 1 && !visited[0][j]) {
                    q.push({0, j});
                    visited[0][j] = true;
                }
                if (grid[m - 1][j] == 1 && !visited[m - 1][j]) {
                    q.push({m - 1, j});
                    visited[m - 1][j] = true;
                }
            }

            for (int i = 0; i < m; i++) {
                if (grid[i][0] == 1 && !visited[i][0]) {
                    q.push({i, 0});
                    visited[i][0] = true;
                }
                if (grid[i][n - 1] == 1 && !visited[i][n - 1]) {
                    q.push({i, n - 1});
                    visited[i][n - 1] = true;
                }
            }

            // Step 2: BFS traversal to mark reachable land cells
            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            while (!q.empty()) {
                pair<int, int> curr = q.front(); q.pop();
                int r = curr.first;
                int c = curr.second;

                for (auto dir : directions) {
                    int nr = r + dir.first;
                    int nc = c + dir.second;

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                        grid[nr][nc] == 1 && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }

            // Step 3: Count unvisited land cells as enclaves
            int count = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == 1 && !visited[i][j]) {
                        count++;
                    }
                }
            }

            return count;
        }
    };

/* ========================================================================
 * PROBLEM 785: IS GRAPH BIPARTITE? (LeetCode)
 * ======================================================================== */

/**
 * @brief Check if the given graph is bipartite using DFS
 *
 * PROBLEM STATEMENT:
 * Given an undirected graph represented as an adjacency list,
 * determine whether it is bipartite. A graph is bipartite if the nodes
 * can be divided into two sets such that no two nodes within the same
 * set are adjacent.
 *
 * EXAMPLE:
 * Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
 * Output: false
 *
 * @param graph Adjacency list of the graph
 * @return true if the graph is bipartite, false otherwise
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) - for color/visited array and recursion stack
 */

// ====================== DFS APPROACH ======================

class Solution {
    public:
        bool dfs(vector<vector<int>>& graph, int node, vector<int>& color, int currColor) {
            color[node] = currColor;

            for(auto neighbour : graph[node]) {
                if(color[node] == color[neighbour]) {
                    return false;
                }
                if(color[neighbour] == -1) {
                    if(dfs(graph, neighbour, color, 1 - currColor) == false) { // If its 1 it becomes 0 and if its 0 then it becomes 1
                        return false;
                    }
                }
            }
            return true;
        }

        bool isBipartite(vector<vector<int>>& graph) {
            // make the color
            int n = graph.size();
            vector<int> color(n, -1); // This will also work as visited array

            // color0 = 0, color1 = 1;

            for(int i = 0; i < n; i++) {
                if(color[i] == -1) {
                    if(dfs(graph, i, color, 0) == false) {
                        return false;
                    }
                }
            }
            return true;
        }
    };

// ====================== BFS APPROACH ======================

/**
 * @brief Check if the given graph is bipartite using BFS
 *
 * @param graph Adjacency list of the graph
 * @return true if the graph is bipartite, false otherwise
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) - for color array and queue
 */

class Solution {
    public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1); // -1 = unvisited

        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;

                while (!q.empty()) {
                    int node = q.front(); q.pop();

                    for (int neighbor : graph[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

/* ===================================================================
 * PROBLEM 802: FIND EVENTUAL SAFE STATES (LeetCode)
 * =================================================================== */

/**
 * @brief Return all eventual safe nodes in a directed graph using DFS
 *
 * PROBLEM STATEMENT:
 * A node is called **eventually safe** if every possible path starting from
 * that node leads to a terminal node (i.e., a node with no outgoing edges).
 *
 * Given a directed graph represented as an adjacency list, return a sorted list
 * of all the **eventual safe nodes**.
 *
 * APPROACH:
 * - Use DFS to detect cycles using `visited` and `pathVisited`.
 * - Nodes involved in cycles or leading to cycles are not safe.
 * - A node is safe if it does not lie on any cycle path.
 *
 * STRATEGY:
 * - If a node is part of a cycle, or leads to one → mark unsafe.
 * - After all DFS calls, nodes not in the current recursion path (pathVisited)
 *   are safe nodes.
 *
 * @param graph Adjacency list of the directed graph
 * @return vector<int> of all safe node indices in sorted order
 *
 * @complexity
 * Time: O(V + E)
 * Space: O(V) for visited, pathVisited arrays and recursion stack
 */

 class Solution {
    public:
        // Helper DFS to detect cycles
        bool hasCycleDFS(vector<vector<int>>& graph, int node,
                         vector<bool>& visited, vector<bool>& pathVisited) {
            visited[node] = true;
            pathVisited[node] = true;

            for (int neighbour : graph[node]) {
                if (!visited[neighbour]) {
                    if (hasCycleDFS(graph, neighbour, visited, pathVisited)) {
                        return true;
                    }
                } else if (pathVisited[neighbour]) {
                    // A back edge found → cycle
                    return true;
                }
            }

            pathVisited[node] = false; // Backtrack
            return false;
        }

        vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
            int n = graph.size();
            vector<bool> visited(n, false);
            vector<bool> pathVisited(n, false);
            vector<int> safeNodes;

            // Step 1: DFS on all nodes to find unsafe/cyclic ones
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    hasCycleDFS(graph, i, visited, pathVisited);
                }
            }

            // Step 2: Nodes not part of any cycle are safe
            for (int i = 0; i < n; i++) {
                if (pathVisited[i] == false) {
                    safeNodes.push_back(i);
                }
            }

            return safeNodes;
        }
    };

/* ===================================================================
 * PROBLEM 207: COURSE SCHEDULE (LeetCode)
 * =================================================================== */

/**
 * @brief Determine if all courses can be finished (i.e., graph is a DAG)
 *
 * PROBLEM STATEMENT:
 * There are `numCourses` labeled from 0 to numCourses - 1. Some courses have
 * prerequisites in the form [a, b], meaning to take course a, you must first
 * take course b.
 *
 * Return true if it is possible to finish all courses. Otherwise, return false.
 *
 * In graph terms, check if the directed graph formed by prerequisites is a DAG.
 *
 * APPROACH:
 * - Use **Kahn's Algorithm** (Topological Sort using indegree).
 * - Count how many nodes can be processed with zero indegree.
 * - If all nodes are processed → valid DAG → all courses can be finished.
 *
 * STRATEGY:
 * - Build an adjacency list for the graph.
 * - Track indegree of each node.
 * - Use a queue to process nodes with indegree 0.
 * - If the count of processed nodes equals total nodes, return true.
 *
 * @param numCourses Total number of courses (nodes)
 * @param prerequisites List of [a, b] pairs meaning b → a
 * @return true if all courses can be finished, else false
 *
 * @complexity
 * Time: O(V + E) — where V = numCourses, E = prerequisites
 * Space: O(V + E) — for adjacency list and indegree array
 */

 class Solution {
    public:
        // Helper function to check if graph is DAG using Kahn's Algorithm
        bool isDAG(vector<vector<int>>& adj, vector<int>& indegree) {
            int n = indegree.size();
            int count = 0;
            queue<int> q;

            // Add all nodes with 0 indegree
            for (int i = 0; i < n; i++) {
                if (indegree[i] == 0) {
                    q.push(i);
                }
            }

            // Kahn's Algorithm main loop
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                count++;

                for (int neighbour : adj[node]) {
                    indegree[neighbour]--;
                    if (indegree[neighbour] == 0) {
                        q.push(neighbour);
                    }
                }
            }

            // If all nodes are processed → graph is a DAG
            return count == n;
        }

        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
            vector<vector<int>> adj(numCourses);
            vector<int> indegree(numCourses, 0);

            // Build graph and indegree array
            for (const auto& pre : prerequisites) {
                int a = pre[0];
                int b = pre[1];
                // b → a (b must be done before a)
                adj[b].push_back(a);
                indegree[a]++;
            }

            return isDAG(adj, indegree);
        }
    };

/* ===================================================================
 * PROBLEM 210: COURSE SCHEDULE II (LeetCode)
 * =================================================================== */

/**
 * @brief Return a valid order in which all courses can be completed
 *
 * PROBLEM STATEMENT:
 * You are given the total number of courses `numCourses` and a list of prerequisite pairs.
 * Each pair [a, b] indicates that to take course `a`, you must first take course `b`.
 *
 * Return a possible ordering of courses to finish all courses.
 * If it is not possible to complete all courses (i.e., there’s a cycle), return an empty list.
 *
 * APPROACH:
 * - Use **Kahn’s Algorithm** (Topological Sort using BFS and indegree tracking).
 * - If the topological ordering contains all nodes → return the result.
 * - If not → a cycle exists → return empty list.
 *
 * STRATEGY:
 * 1. Build the adjacency list for the directed graph.
 * 2. Track indegrees for each node.
 * 3. Start from nodes with zero indegree, and process using a queue.
 * 4. Append processed nodes to the topological ordering list.
 *
 * @param numCourses Total number of nodes (courses)
 * @param prerequisites Prerequisite edges [a, b] meaning b → a
 * @return vector<int> A valid ordering of courses or empty vector if cycle exists
 *
 * @complexity
 * Time: O(V + E), where V = numCourses and E = number of prerequisites
 * Space: O(V + E), for adjacency list, indegree array, and queue
 */

 class Solution {
    public:
        // Helper function to perform Kahn's Topological Sort
        void topologicalSort(int numCourses, vector<vector<int>>& adj, vector<int>& indegree, vector<int>& topo) {
            queue<int> q;

            // Push all nodes with zero indegree into the queue
            for (int i = 0; i < numCourses; i++) {
                if (indegree[i] == 0) {
                    q.push(i);
                }
            }

            // BFS traversal
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                topo.push_back(node);

                // Decrease indegree of all adjacent nodes
                for (int neighbour : adj[node]) {
                    indegree[neighbour]--;
                    if (indegree[neighbour] == 0) {
                        q.push(neighbour);
                    }
                }
            }
        }

        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<vector<int>> adj(numCourses);       // Adjacency list
            vector<int> indegree(numCourses, 0);       // Indegree array

            // Step 1: Build the graph and populate indegree
            for (const auto& p : prerequisites) {
                int a = p[0];
                int b = p[1];
                // Edge: b → a (b must be completed before a)
                adj[b].push_back(a);
                indegree[a]++;
            }

            // Step 2: Perform topological sort
            vector<int> topo;
            topologicalSort(numCourses, adj, indegree, topo);

            // Step 3: If topological sort includes all nodes, return it
            if (topo.size() == numCourses) {
                return topo;
            }

            // Cycle detected: return empty vector
            return {};
        }
    };

/* ===================================================================
 * PROBLEM 269: ALIEN DICTIONARY (LeetCode)
 * =================================================================== */

/**
 * @brief Determine the order of characters in an alien language
 *
 * PROBLEM STATEMENT:
 * You are given a list of words sorted lexicographically according to the rules
 * of an unknown alien language. You must derive the order of characters in the alien alphabet.
 *
 * If the ordering is invalid (e.g., a prefix appears after its full word), return "".
 * If multiple valid orderings exist, return any one of them.
 *
 * EXAMPLE:
 * Input:  words = ["wrt","wrf","er","ett","rftt"]
 * Output: "wertf"
 *
 * APPROACH:
 * - Build a graph of characters using pairwise comparisons of adjacent words.
 * - If char1 comes before char2 → add edge: char1 → char2.
 * - Use Kahn’s Algorithm (BFS Topological Sort) to determine character order.
 *
 * STRATEGY:
 * 1. Initialize graph (adjacency list) and indegree map.
 * 2. For each pair of adjacent words, compare characters and build edges.
 * 3. Apply topological sort using queue to find valid order.
 * 4. If result length != total unique characters → cycle exists → return "".
 *
 * @param words Vector of words sorted by alien dictionary
 * @return string A valid character order or "" if not possible
 *
 * @complexity
 * Time:  O(N * L), where N = number of words, L = average word length
 * Space: O(1), since alphabet is limited to 26 characters
 */

 class Solution {
    public:
        string alienOrder(vector<string>& words) {
            unordered_map<char, unordered_set<char>> adj; // adjacency list
            unordered_map<char, int> indegree;            // indegree of each node

            // Step 1: Initialize graph nodes
            for (const string& word : words) {
                for (char c : word) {
                    indegree[c] = 0;  // Ensure every character is in the indegree map
                }
            }

            // Step 2: Build the graph from adjacent word pairs
            for (int i = 0; i < words.size() - 1; ++i) {
                string& w1 = words[i];
                string& w2 = words[i + 1];

                // Invalid case: longer word appears before its prefix
                if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) {
                    return "";
                }

                // Compare characters to find the first difference
                for (int j = 0; j < min(w1.size(), w2.size()); ++j) {
                    char c1 = w1[j];
                    char c2 = w2[j];

                    if (c1 != c2) {
                        // Add edge only if not already present
                        if (!adj[c1].count(c2)) {
                            adj[c1].insert(c2);
                            indegree[c2]++;
                        }
                        break; // Only first differing character matters
                    }
                }
            }

            // Step 3: Kahn’s Algorithm (Topological Sort using BFS)
            queue<char> q;
            for (auto& [c, deg] : indegree) {
                if (deg == 0) {
                    q.push(c);
                }
            }

            string result;
            while (!q.empty()) {
                char c = q.front();
                q.pop();
                result += c;

                for (char neighbor : adj[c]) {
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0) {
                        q.push(neighbor);
                    }
                }
            }

            // Step 4: Check if all characters are included in result
            return result.size() == indegree.size() ? result : "";
        }
    };

/* =============================================================================
 * PROBLEM 990: SATISFIABILITY OF EQUALITY EQUATIONS (LeetCode)
 * ============================================================================= */

/**
 * @brief Determine if all given equality and inequality equations are satisfiable
 *
 * PROBLEM STATEMENT:
 * You are given an array of strings `equations` of length n representing relationships between variables.
 * Each equation is of the form "a==b" or "a!=b", where a and b are lowercase English letters.
 * Return true if it is possible to assign integers to variable names such that all equations are satisfied.
 *
 * EXAMPLE:
 * Input: ["a==b","b!=a"]
 * Output: false
 *
 * APPROACH:
 * - Use Disjoint Set Union (DSU) to group variables connected by equality (==).
 * - Then, for every inequality (!=), check if both variables belong to the same group.
 * - If they do, it's a contradiction → return false.
 *
 * ALGORITHM:
 * 1. Initialize DSU for 26 lowercase letters.
 * 2. Process all equations with `==` and perform union.
 * 3. Process all equations with `!=` and check for contradiction.
 *
 * COMPLEXITY:
 * Time: O(N * α(26)) ≈ O(N), where N = number of equations
 * Space: O(26)
 */

 class Solution {
    public:
        vector<int> parent;
        vector<int> rank;

        // FIND operation with path compression
        int findParent(int x) {
            if (parent[x] == x) return x;
            return parent[x] = findParent(parent[x]);
        }

        // UNION operation by rank
        void Union(int x, int y) {
            int px = findParent(x);
            int py = findParent(y);

            if (px == py) return;

            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }

        bool equationsPossible(vector<string>& equations) {
            parent.resize(26);
            rank.resize(26, 0);

            // Step 1: Initialize parent of each variable to itself
            for (int i = 0; i < 26; i++) {
                parent[i] = i;
            }

            // Step 2: Union all equal variables
            for (const string& eq : equations) {
                if (eq[1] == '=') {
                    int u = eq[0] - 'a';
                    int v = eq[3] - 'a';
                    Union(u, v);
                }
            }

            // Step 3: Check all not-equal constraints
            for (const string& eq : equations) {
                if (eq[1] == '!') {
                    int u = eq[0] - 'a';
                    int v = eq[3] - 'a';

                    if (findParent(u) == findParent(v)) {
                        return false; // Contradiction found
                    }
                }
            }

            return true; // No contradiction
        }
    };

/* =============================================================================
 * PROBLEM 1319: NUMBER OF OPERATIONS TO MAKE NETWORK CONNECTED (LeetCode)
 * ============================================================================= */

/**
 * @brief Connect all computers in a network using the minimum number of operations
 *
 * PROBLEM STATEMENT:
 * - There are `n` computers labeled from `0` to `n - 1`.
 * - Given a list of connections where `connections[i] = [a, b]` represents a direct connection.
 * - You can remove and reconnect cables.
 * - Return the minimum number of operations needed to connect all computers.
 * - If it is not possible, return -1.
 *
 * EXAMPLE:
 * Input: n = 4, connections = [[0,1],[0,2],[1,2]]
 * Output: 1
 *
 * APPROACH:
 * - Use Disjoint Set Union (DSU) to find connected components.
 * - If total connections < n - 1 → impossible to connect → return -1.
 * - Otherwise, count how many components exist.
 * - To connect `k` components into one, you need `k - 1` cables.
 *
 * TIME COMPLEXITY: O(E * α(N)) where E = connections.size(), α = inverse Ackermann
 * SPACE COMPLEXITY: O(N)
 */

 class Solution {
    public:
        vector<int> parent;
        vector<int> rank;

        // FIND with path compression
        int findParent(int x) {
            if (parent[x] == x) return x;
            return parent[x] = findParent(parent[x]);
        }

        // UNION by rank
        void Union(int x, int y) {
            int px = findParent(x);
            int py = findParent(y);

            if (rank[px] > rank[py]) {
                parent[py] = px;
            } else if (rank[py] > rank[px]) {
                parent[px] = py;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }

        int makeConnected(int n, vector<vector<int>>& connections) {
            // Not enough cables to connect all computers
            if (connections.size() < n - 1) return -1;

            parent.resize(n);
            rank.resize(n, 0);

            // Step 1: Initialize each computer to be its own parent
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }

            int components = n;

            // Step 2: Union operation for each connection
            for (auto& edge : connections) {
                int u = edge[0];
                int v = edge[1];

                int pu = findParent(u);
                int pv = findParent(v);

                if (pu != pv) {
                    Union(u, v);
                    components--; // Successfully connected two components
                }
            }

            // Step 3: We need (components - 1) operations to connect them
            return components - 1;
        }
    };

/* =============================================================================
 * PROBLEM 2316: COUNT UNREACHABLE PAIRS OF NODES IN AN UNDIRECTED GRAPH (LeetCode)
 * ============================================================================= */

/**
 * @brief Count the number of unordered pairs of nodes that are unreachable from each other.
 *
 * PROBLEM STATEMENT:
 * You are given an integer `n` (total number of nodes labeled 0 to n - 1) and
 * a 2D array `edges` where `edges[i] = [a, b]` represents an undirected edge.
 *
 * Return the number of **unreachable node pairs** in the graph.
 *
 * EXAMPLE:
 * Input: n = 5, edges = [[0,1],[2,3],[0,4]]
 * Output: 6
 *
 * EXPLANATION:
 * - Components: {0,1,4} and {2,3}
 * - Unreachable pairs = 3 * 2 = 6 (from each pair of distinct components)
 *
 * APPROACH:
 * - Use DSU to find connected components.
 * - Count the size of each component.
 * - For each component of size `s`, it contributes `s * (remaining - s)` unreachable pairs.
 *
 * @complexity
 * Time: O(n + e * α(n)) where e = edges.size(), α is inverse Ackermann
 * Space: O(n)
 */

 class Solution {
    public:
        vector<int> parent;
        vector<int> rank;

        // DSU: Find with path compression
        int findParent(int x) {
            if (parent[x] == x) return x;
            return parent[x] = findParent(parent[x]);
        }

        // DSU: Union by rank
        void Union(int x, int y) {
            int px = findParent(x);
            int py = findParent(y);

            if (px == py) return;

            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }

        long long countPairs(int n, vector<vector<int>>& edges) {
            parent.resize(n);
            rank.resize(n, 0);

            // Step 1: Initialize each node as its own parent
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }

            // Step 2: Union all connected nodes
            for (auto& edge : edges) {
                Union(edge[0], edge[1]);
            }

            // Step 3: Count size of each component using parent map
            unordered_map<int, int> componentSize;
            for (int i = 0; i < n; i++) {
                int p = findParent(i);
                componentSize[p]++;
            }

            // Step 4: Count unreachable pairs
            long long totalPairs = 0;
            long long remaining = n;

            for (auto& [leader, size] : componentSize) {
                totalPairs += size * (remaining - size);
                remaining -= size;
            }

            return totalPairs;
        }
    };

/* ===================================================================
 * PROBLEM 743: NETWORK DELAY TIME (LeetCode)
 * =================================================================== */

/**
 * @brief Find the time it takes for all nodes to receive a signal from a source node.
 *
 * PROBLEM STATEMENT:
 * You are given a directed weighted graph with `n` nodes labeled from 1 to `n`,
 * and a list of travel times as directed edges `times[i] = [u, v, w]`,
 * where `u` sends a signal to `v` with a time delay of `w`.
 *
 * Return the minimum time it takes for all the `n` nodes to receive the signal from the source `k`.
 * If it is impossible for all nodes to receive the signal, return `-1`.
 *
 * APPROACH:
 * - Build an adjacency list to represent the graph.
 * - Use Dijkstra's Algorithm (min-heap) to find the shortest time from node `k` to all others.
 * - Track the time to reach each node using a `time[]` array.
 * - The result is the maximum value in the `time[]` array (i.e., the longest minimum delay).
 *
 * @complexity
 * Time: O((V + E) * log V)
 * Space: O(V + E)
 */

 class Solution {
    public:
        int networkDelayTime(vector<vector<int>>& times, int n, int k) {
            // Step 1: Build the adjacency list
            vector<vector<pair<int, int>>> adj(n + 1);
            for (auto vec : times) {
                int u = vec[0];
                int v = vec[1];
                int w = vec[2];
                adj[u].push_back({v, w});
            }

            // Step 2: Initialize min-heap and distance array
            vector<int> time(n + 1, INT_MAX);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

            time[k] = 0;
            pq.push({0, k}); // {delayTime, node}

            // Step 3: Dijkstra’s Algorithm
            while (!pq.empty()) {
                auto [d, node] = pq.top();
                pq.pop();

                for (auto [neighbor, weight] : adj[node]) {
                    if (d + weight < time[neighbor]) {
                        time[neighbor] = d + weight;
                        pq.push({time[neighbor], neighbor});
                    }
                }
            }

            // Step 4: Compute max delay time among all nodes
            int maxTime = 0;
            for (int i = 1; i <= n; i++) {
                if (time[i] == INT_MAX) return -1; // unreachable node
                maxTime = max(maxTime, time[i]);
            }

            return maxTime;
        }
    };

/* ===================================================================
 * PROBLEM 1091: SHORTEST PATH IN BINARY MATRIX (LeetCode)
 * =================================================================== */

/**
 * @brief Find the shortest path from top-left to bottom-right in a binary matrix.
 *
 * PROBLEM:
 * - You are given an n x n binary matrix `grid` where 0 represents an empty cell
 *   and 1 represents an obstacle.
 * - Return the length of the shortest clear path from (0, 0) to (n-1, n-1) using 8 directions.
 * - Return -1 if no such path exists.
 *
 * APPROACH:
 * - Perform BFS starting from (0, 0).
 * - Track distance as you visit new cells.
 * - Use 8-directional movement.
 *
 * @complexity
 * Time: O(n^2)
 * Space: O(n^2)
 */

 class Solution {
    public:
        int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
            int n = grid.size();

            // Check if start or end is blocked
            if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;

            vector<pair<int, int>> directions = {
                {1, 0}, {0, 1}, {-1, 0}, {0, -1},
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            };

            queue<pair<int, int>> q;
            q.push({0, 0});
            grid[0][0] = 1;  // Distance from start is 1

            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                int dist = grid[x][y];

                if (x == n - 1 && y == n - 1) return dist; // Reached destination

                for (auto [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 0) {
                        grid[nx][ny] = dist + 1;
                        q.push({nx, ny});
                    }
                }
            }

            return -1; // No path exists
        }
    };

/**
 * @brief Solve the same problem using Dijkstra's Algorithm with a min-heap.
 *
 * NOTE: Although Dijkstra is generally used for weighted graphs, here we can
 * simulate it for uniform weights to demonstrate priority queue usage.
 *
 * @complexity
 * Time: O(n^2 * log n)
 * Space: O(n^2)
 */

 class Solution {
    public:
        int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
            int n = grid.size();
            if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;

            vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
            dist[0][0] = 1;

            vector<pair<int, int>> directions = {
                {1, 0}, {0, 1}, {-1, 0}, {0, -1},
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            };

            // Min-heap: {distance, {x, y}}
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

            pq.push({1, {0, 0}});

            while (!pq.empty()) {
                auto [d, cell] = pq.top(); pq.pop();
                int x = cell.first;
                int y = cell.second;

                if (x == n - 1 && y == n - 1) return d;

                for (auto [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 0) {
                        if (d + 1 < dist[nx][ny]) {
                            dist[nx][ny] = d + 1;
                            pq.push({dist[nx][ny], {nx, ny}});
                        }
                    }
                }
            }

            return -1;
        }
    };

/* ===================================================================
 * PROBLEM 1631: PATH WITH MINIMUM EFFORT (LeetCode)
 * =================================================================== */

/**
 * @brief Find a path from (0, 0) to (m-1, n-1) minimizing the maximum height difference.
 *
 * PROBLEM:
 * - You are given an `m x n` grid of integers `heights`.
 * - A path is valid if at each step you move to an adjacent cell (up/down/left/right).
 * - The *effort* of a path is the **maximum absolute difference** in heights between adjacent cells.
 * - Return the minimum possible *effort* needed to reach the bottom-right from the top-left.
 *
 * APPROACH (Dijkstra’s Algorithm):
 * - Treat each cell as a node, and each move to a neighbor as an edge with a weight = abs(height difference).
 * - The goal is to minimize the **maximum edge weight** on the path from source to destination.
 * - Use a min-heap (priority queue) to always pick the path with the least *effort so far*.
 * - For each neighbor, compute the maximum effort along that path and update it if it's better.
 *
 * COMPLEXITY:
 * - Time: O(m * n * log(m * n)) because each cell is pushed to the heap at most once
 * - Space: O(m * n) for the result matrix and priority queue
 */

 class Solution {
    public:
        int minimumEffortPath(vector<vector<int>>& heights) {
            int m = heights.size();
            int n = heights[0].size();

            // result[i][j] stores the minimum effort needed to reach cell (i, j)
            vector<vector<int>> result(m, vector<int>(n, INT_MAX));
            result[0][0] = 0;

            // Min-heap: stores {effort to reach, {x, y}}
            priority_queue<
                pair<int, pair<int, int>>,
                vector<pair<int, pair<int, int>>>,
                greater<>
            > pq;

            pq.push({0, {0, 0}}); // Start from the top-left cell

            // 4-directional movement (up, down, left, right)
            vector<pair<int, int>> directions = {
                {1, 0}, {0, 1}, {-1, 0}, {0, -1}
            };

            while (!pq.empty()) {
                auto [currEffort, coords] = pq.top(); pq.pop();
                auto [x, y] = coords;

                // If we've reached the destination cell, return the current effort
                if (x == m - 1 && y == n - 1) return currEffort;

                // Visit all 4 neighbors
                for (auto [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // Make sure neighbor is within grid bounds
                    if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                        // Calculate the effort to move to neighbor
                        int diff = abs(heights[nx][ny] - heights[x][y]);
                        int newEffort = max(currEffort, diff); // max of path so far and current edge

                        // If this path offers a smaller max effort to reach (nx, ny), update it
                        if (newEffort < result[nx][ny]) {
                            result[nx][ny] = newEffort;
                            pq.push({newEffort, {nx, ny}});
                        }
                    }
                }
            }

            return 0; // Fallback, although the problem guarantees reachability
        }
    };

/* ===================================================================
 * PROBLEM 1584: MINIMUM COST TO CONNECT ALL POINTS (USING PRIM'S MST)
 * =================================================================== */

/**
 * @brief Find the minimum cost to connect all points in 2D space
 *
 * PROBLEM STATEMENT:
 * Given `n` points in a 2D plane, you are to connect all points such that the total cost is minimized.
 * The cost to connect two points (x1, y1) and (x2, y2) is the **Manhattan Distance**:
 *   cost = |x1 - x2| + |y1 - y2|
 *
 * You can connect any two points directly; the goal is to **connect all points with minimum total cost**
 * such that all nodes are reachable (Minimum Spanning Tree).
 *
 * Input:
 * - vector<vector<int>> points: where points[i] = {xi, yi}
 *
 * Output:
 * - Integer value representing minimum total cost to connect all points
 *
 * APPROACH (Prim's Algorithm for MST):
 * - Construct a complete graph using Manhattan distances
 * - Apply Prim’s algorithm with Min-Heap to find MST cost
 *
 * COMPLEXITY:
 * - Time: O(N^2 * log N) due to dense graph and priority queue
 * - Space: O(N^2) for adjacency list
 */

 class Solution {
    public:
        /**
         * @brief Prim's algorithm to compute MST cost from adjacency list
         * @param adj: Adjacency list of the graph {neighbour, cost}
         * @param n: Number of nodes
         * @return Total cost of the Minimum Spanning Tree
         */
        int primsAlgo(vector<vector<pair<int, int>>>& adj, int n) {
            // Min-heap: {cost, node}
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

            vector<bool> inMST(n, false); // Mark nodes already included in MST
            int minCost = 0;

            pq.push({0, 0}); // Start from node 0 with 0 cost

            while (!pq.empty()) {
                auto [cost, node] = pq.top();
                pq.pop();

                if (inMST[node]) continue;

                inMST[node] = true;
                minCost += cost;

                // Add all neighbors of current node to the heap
                for (auto [neighbour, neighbourCost] : adj[node]) {
                    if (!inMST[neighbour]) {
                        pq.push({neighbourCost, neighbour});
                    }
                }
            }

            return minCost;
        }

        /**
         * @brief Main function to compute the minimum cost to connect all given points
         */
        int minCostConnectPoints(vector<vector<int>>& points) {
            int n = points.size();

            // Step 1: Build complete graph with Manhattan distances
            vector<vector<pair<int, int>>> adj(n); // adj[u] = {v, cost}
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                    adj[i].push_back({j, cost});
                    adj[j].push_back({i, cost});
                }
            }

            // Step 2: Apply Prim's algorithm to get MST cost
            return primsAlgo(adj, n);
        }
    };

/* ===================================================================
 * LEETCODE 433: MINIMUM GENETIC MUTATION
 * =================================================================== */

/**
 * @brief Find the minimum number of mutations to transform startGene to endGene
 *
 * PROBLEM STATEMENT:
 * A gene string is a string of length 8, consisting of characters 'A', 'C', 'G', and 'T'.
 * A **mutation** involves changing a single character to any of the other three choices.
 *
 * You are given:
 * - A start gene string `startGene`
 * - A target gene string `endGene`
 * - A bank of valid intermediate gene strings `bank`
 *
 * Return the **minimum number of mutations** needed to transform startGene to endGene.
 * Each intermediate mutation must be present in the `bank`.
 * If no such mutation path exists, return -1.
 *
 * Input:
 * - string startGene: starting gene (length = 8)
 * - string endGene: target gene (length = 8)
 * - vector<string> bank: valid intermediate genes
 *
 * Output:
 * - Integer: Minimum number of mutations, or -1 if not possible
 *
 * ALGORITHM (BFS - Shortest Path in Unweighted Graph):
 * - Treat each gene string as a node
 * - Two gene strings are connected if they differ by exactly one character
 * - Use BFS to find the shortest path from startGene to endGene
 *
 * COMPLEXITY:
 * - Time: O(N * 8 * 4), where N = bank size, 8 is gene length, 4 is number of possible bases
 * - Space: O(N) for visited and bank set
 */

 class Solution {
    public:
        int minMutation(string startGene, string endGene, vector<string>& bank) {
            // Initialize queue for BFS
            queue<string> q;

            // Convert bank to set for O(1) lookup
            unordered_set<string> bankset(begin(bank), end(bank));
            unordered_set<string> visited;

            q.push(startGene);
            visited.insert(startGene);

            int level = 0; // Level indicates number of mutations

            while (!q.empty()) {
                int size = q.size();

                while (size--) {
                    string curr = q.front();
                    q.pop();

                    // If we reach the target gene
                    if (curr == endGene) return level;

                    // Try mutating each position with A, T, G, C
                    for (char ch : "ATGC") {
                        for (int i = 0; i < curr.length(); i++) {
                            string neighbour = curr;
                            neighbour[i] = ch;

                            // Only consider valid mutations
                            if (visited.find(neighbour) == visited.end() && bankset.find(neighbour) != bankset.end()) {
                                q.push(neighbour);
                                visited.insert(neighbour);
                            }
                        }
                    }
                }

                level++; // Move to next level (next mutation)
            }

            return -1; // Mutation not possible
        }
    };

/* ===================================================================
 * LEETCODE 947: MOST STONES REMOVED WITH SAME ROW OR COLUMN
 * =================================================================== */

/**
 * @brief Remove the maximum number of stones from a 2D grid
 *
 * PROBLEM STATEMENT:
 * You are given a list of stones where each stone is at position (x, y) on a 2D grid.
 * A stone can be removed **if there is another stone in the same row or column**.
 *
 * Return the **maximum number of stones that can be removed**.
 *
 * Note: You can only remove a stone if it shares a row or column with at least one other remaining stone.
 *
 * Input:
 * - vector<vector<int>> stones: list of stone coordinates
 *
 * Output:
 * - Integer: Maximum number of stones that can be removed
 *
 * EXAMPLE:
 * Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
 * Output: 5
 * Explanation: We can remove 5 stones, one per move, leaving one isolated stone.
 *
 * ALGORITHM (DFS + Connected Components):
 * - Treat each stone as a node in a graph
 * - Connect two stones if they share a row or column
 * - Count number of connected components using DFS
 * - Answer = total stones - number of connected components
 *
 * COMPLEXITY:
 * - Time: O(N^2), where N is the number of stones (due to pairwise comparisons)
 * - Space: O(N) for visited array
 */

 class Solution {
    public:
        /**
         * @brief DFS to mark all connected stones (same row or column)
         */
        void dfs(vector<vector<int>>& stones, int index, vector<bool>& visited) {
            int n = stones.size();
            visited[index] = true;

            int r = stones[index][0];
            int c = stones[index][1];

            // Traverse all other stones and visit connected ones
            for (int i = 0; i < n; i++) {
                if (!visited[i] && (stones[i][0] == r || stones[i][1] == c)) {
                    dfs(stones, i, visited);
                }
            }
        }

        /**
         * @brief Main function to compute max removable stones
         */
        int removeStones(vector<vector<int>>& stones) {
            int n = stones.size();
            vector<bool> visited(n, false);

            int group = 0; // Count connected components (islands)

            // Use DFS to find all connected components
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    dfs(stones, i, visited);
                    group++;
                }
            }

            return n - group; // Max stones removed = total - groups
        }
    };

/* ===================================================================
 * LEETCODE 1926: NEAREST EXIT FROM ENTRANCE IN MAZE
 * =================================================================== */

/**
 * @brief Find the minimum number of steps to reach the nearest exit from the entrance
 *
 * PROBLEM STATEMENT:
 * You are given a `m x n` maze represented by a 2D grid of characters:
 * - '.' = open cell
 * - '+' = wall
 *
 * Also given is the `entrance` coordinate in the maze.
 * An **exit** is any cell on the boundary of the maze that is an open cell ('.') and **not** the entrance.
 *
 * Return the **minimum number of steps** required to reach the nearest exit.
 * If there is no possible exit, return -1.
 *
 * Input:
 * - vector<vector<char>> maze: 2D maze grid
 * - vector<int> entrance: starting position {row, col}
 *
 * Output:
 * - Integer: Minimum steps to nearest exit, or -1 if unreachable
 *
 * EXAMPLE:
 * Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
 * Output: 1
 *
 * ALGORITHM (BFS - Shortest Path in Unweighted Grid):
 * - Use BFS to explore all possible paths
 * - Track visited cells to avoid cycles
 * - First time we reach an exit cell, return the number of steps
 *
 * COMPLEXITY:
 * - Time: O(M * N) where M = rows, N = cols
 * - Space: O(M * N) for visited tracking
 */

 class Solution {
    public:
        int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
            int m = maze.size();
            int n = maze[0].size();

            // Queue for BFS: {row, col}
            queue<pair<int, int>> q;
            vector<vector<bool>> visited(m, vector<bool>(n, false));

            // 4 directions: down, right, up, left
            vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

            int er = entrance[0];
            int ec = entrance[1];

            visited[er][ec] = true;
            q.push({er, ec});

            int step = 0; // Number of steps from entrance

            while (!q.empty()) {
                int size = q.size();

                while (size--) {
                    auto [r, c] = q.front();
                    q.pop();

                    // If current cell is on boundary and not the entrance, return step
                    if ((r == 0 || r == m - 1 || c == 0 || c == n - 1) && (r != er || c != ec)) {
                        return step;
                    }

                    // Explore 4 directions
                    for (auto [dr, dc] : directions) {
                        int nr = r + dr;
                        int nc = c + dc;

                        // If next cell is valid and not visited and is open
                        if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                            maze[nr][nc] == '.' && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q.push({nr, nc});
                        }
                    }
                }

                step++; // Move to next level
            }

            return -1; // No exit found
        }
    };

/* ===================================================================
 * LEETCODE 1971: FIND IF PATH EXISTS IN GRAPH
 * =================================================================== */

/**
 * @brief Determine if there is a valid path between source and destination
 *
 * PROBLEM STATEMENT:
 * You are given an **undirected graph** with `n` nodes numbered from 0 to n - 1.
 * You are also given a list of `edges` where each edge connects two nodes.
 *
 * Given a `source` node and a `destination` node, return `true` if there is a valid path
 * between the two, or `false` otherwise.
 *
 * Input:
 * - Integer `n`: number of nodes
 * - vector<vector<int>> edges: list of undirected edges
 * - Integer `source`: start node
 * - Integer `destination`: target node
 *
 * Output:
 * - Boolean: true if path exists, false otherwise
 *
 * EXAMPLE:
 * Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
 * Output: false
 *
 * ALGORITHM (DFS Traversal):
 * - Build the adjacency list from edge list
 * - Perform DFS from the source
 * - If destination is found during DFS, return true
 *
 * COMPLEXITY:
 * - Time: O(V + E)
 * - Space: O(V + E) for adjacency list and visited array
 */

 class Solution {
    public:
        /**
         * @brief DFS to find if destination is reachable from source
         */
        bool dfs(vector<vector<int>>& adj, int source, int destination, vector<bool>& visited) {
            if (source == destination) return true;

            visited[source] = true;

            for (auto neighbour : adj[source]) {
                if (!visited[neighbour] && dfs(adj, neighbour, destination, visited)) {
                    return true;
                }
            }

            return false;
        }

        /**
         * @brief Main function to check if path exists between source and destination
         */
        bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
            vector<vector<int>> adj(n);
            vector<bool> visited(n, false);

            // Build adjacency list
            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            return dfs(adj, source, destination, visited);
        }
    };

/* ===================================================================
 * LEETCODE 841: KEYS AND ROOMS
 * =================================================================== */

/**
 * @brief Determine if all rooms can be visited starting from room 0
 *
 * PROBLEM STATEMENT:
 * There are `n` rooms labeled from 0 to n - 1. Each room contains a list of keys to other rooms.
 * Initially, you are in room 0 and can enter it freely. You can use any key found in a room to enter other rooms.
 *
 * Return `true` if you can visit **all rooms**, otherwise return `false`.
 *
 * Input:
 * - vector<vector<int>> rooms: rooms[i] contains a list of keys to other rooms
 *
 * Output:
 * - Boolean: true if all rooms can be visited, false otherwise
 *
 * EXAMPLE:
 * Input: rooms = [[1], [2], [3], []]
 * Output: true
 * Explanation: Room 0 -> 1 -> 2 -> 3
 *
 * ALGORITHM (DFS Traversal):
 * - Treat rooms as nodes and keys as edges
 * - Perform DFS starting from room 0
 * - Track visited rooms
 * - If all rooms are visited after DFS, return true
 *
 * COMPLEXITY:
 * - Time: O(N + E) where N = number of rooms, E = total number of keys
 * - Space: O(N) for visited array and call stack
 */

 class Solution {
    public:
        /**
         * @brief DFS to explore all rooms accessible from current room
         */
        void dfs(vector<vector<int>>& adj, int node, vector<bool>& visited) {
            visited[node] = true;

            for (auto neighbour : adj[node]) {
                if (!visited[neighbour]) {
                    dfs(adj, neighbour, visited);
                }
            }
        }

        /**
         * @brief Main function to check if all rooms can be visited
         */
        bool canVisitAllRooms(vector<vector<int>>& rooms) {
            int n = rooms.size();

            // Construct adjacency list (rooms -> graph)
            vector<vector<int>> adj(n);
            vector<bool> visited(n, false);

            for (int i = 0; i < n; i++) {
                for (auto key : rooms[i]) {
                    adj[i].push_back(key);
                }
            }

            // Perform DFS from room 0
            dfs(adj, 0, visited);

            // Check if all rooms were visited
            for (int i = 0; i < n; i++) {
                if (!visited[i]) return false;
            }

            return true;
        }
    };

    /* ===================================================================
     * LEETCODE 133: CLONE GRAPH
     * =================================================================== */

    class Node
    {
    public:
        int val;
        vector<Node *> neighbors;
        Node()
        {
            val = 0;
            neighbors = vector<Node *>();
        }
        Node(int _val)
        {
            val = _val;
            neighbors = vector<Node *>();
        }
        Node(int _val, vector<Node *> _neighbors)
        {
            val = _val;
            neighbors = _neighbors;
        }
    };

    /**
     * @brief Clone an undirected graph where each node contains a value and a list of neighbors.
     *
     * ALGORITHM (DFS + HashMap):
     * - Use DFS to traverse the original graph.
     * - Maintain a hashmap to track already cloned nodes (to avoid cycles and re-cloning).
     * - For each node:
     *     - If it's already cloned, use the existing copy.
     *     - Otherwise, clone the node, and recursively clone its neighbors.
     *
     * TIME COMPLEXITY: O(N + E), where:
     * - N is the number of nodes.
     * - E is the number of edges.
     */

    class Solution
    {
        // Map from original node to its clone
        unordered_map<Node *, Node *> mp;

        /**
         * @brief DFS helper to clone neighbors recursively
         *
         * @param node         Current original node
         * @param clone_node   Corresponding cloned node
         */
        void DFS(Node *node, Node *clone_node)
        {
            for (Node *neighbor : node->neighbors)
            {
                if (mp.find(neighbor) == mp.end()) // yet not cloned
                {
                    Node *clone = new Node(neighbor->val); // create the clone
                    mp[neighbor] = clone; // store in map
                    clone_node->neighbors.push_back(clone); // make the clone neighbour of clone_node
                    DFS(neighbor, clone); // recursively call DFS on this
                }
                else // clone is available
                {
                    clone_node->neighbors.push_back(mp[neighbor]); // make the clone neighbour
                }
            }
        }

    public:
        /**
         * @brief Clones the graph starting from given node
         *
         * @param node   Starting node of the original graph
         * @return       Cloned graph's starting node
         */
        Node *cloneGraph(Node *node)
        {
            if (node == NULL)
                return NULL;

            mp.clear();

            Node *clone_node = new Node(node->val);
            mp[node] = clone_node;

            DFS(node, clone_node);

            return clone_node;
        }
    };

    /* ===================================================================
     * LEETCODE 2101: DETONATE THE MAXIMUM BOMBS
     * =================================================================== */

    /**
     * @brief Given a list of bombs where each bomb has coordinates and a radius,
     *        determine the maximum number of bombs that can be detonated starting from any one bomb.
     *
     * ALGORITHM (Graph + DFS):
     * - Treat each bomb as a node.
     * - If bomb A can detonate bomb B (based on Euclidean distance ≤ A's radius), add a directed edge A → B.
     * - Use DFS from each node to count the number of bombs that can be detonated starting from it.
     * - Track and return the maximum count over all possible starting bombs.
     *
     * TIME COMPLEXITY:
     * - Building graph: O(N^2)
     * - DFS per node: O(N + E) → total O(N*(N+E)) in worst case
     */

    class Solution
    {
    public:
        /**
         * @brief DFS to count number of bombs that can be detonated from current node
         *
         * @param node      Current bomb index
         * @param adj       Adjacency list representing detonation graph
         * @param visited   Visited tracker to avoid re-visits
         * @return          Total number of bombs detonated in this DFS chain
         */
        int dfs(int node, vector<vector<int>> &adj, vector<bool> &visited)
        {
            visited[node] = true;
            int count = 1; // Count this bomb

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    count += dfs(neighbor, adj, visited);
                }
            }

            return count;
        }

        /**
         * @brief Compute the maximum number of bombs that can be detonated
         *
         * @param bombs  List of bombs: {x, y, radius}
         * @return       Max number of bombs detonated starting from any bomb
         */
        int maximumDetonation(vector<vector<int>> &bombs)
        {
            int n = bombs.size();
            vector<vector<int>> adj(n); // Adjacency list

            // Step 1: Build the graph
            for (int i = 0; i < n; i++)
            {
                long long x1 = bombs[i][0];
                long long y1 = bombs[i][1];
                long long r = bombs[i][2];

                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                        continue;

                    long long x2 = bombs[j][0];
                    long long y2 = bombs[j][1];

                    long long dx = x1 - x2;
                    long long dy = y1 - y2;
                    long long distSq = dx * dx + dy * dy;

                    // If bomb j is within range of bomb i
                    if (distSq <= r * r)
                    {
                        adj[i].push_back(j);
                    }
                }
            }

            // Step 2: Try DFS from each bomb
            int maxDetonated = 0;

            for (int i = 0; i < n; i++)
            {
                vector<bool> visited(n, false);
                maxDetonated = max(maxDetonated, dfs(i, adj, visited));
            }

            return maxDetonated;
        }
    };

    /* ===================================================================
     * LEETCODE 2097: VALID ARRANGEMENT OF PAIRS
     * =================================================================== */

    /**
     * @brief Given a list of directed pairs [u, v], rearrange them so that:
     *        - For every adjacent pair (a, b) and (b, c), b matches.
     *        - In other words, form a valid Eulerian path from the pairs.
     *
     * ALGORITHM (Hierholzer's Algorithm for Directed Graph):
     * - Build adjacency list and track in-degree/out-degree for all nodes.
     * - Identify the starting node of the Eulerian path:
     *     → It should have out-degree = in-degree + 1
     *     → If none, start with any node
     * - Use a stack to simulate DFS and construct the path in reverse.
     * - Convert the node path into an edge list format.
     *
     * TIME COMPLEXITY: O(E), where E = number of pairs
     */

    class Solution
    {
    public:
        /**
         * @brief Reconstruct a valid arrangement of pairs using Eulerian path
         *
         * @param pairs  List of directed edges [from, to]
         * @return       Sequence of pairs forming a valid path
         */
        vector<vector<int>> validArrangement(vector<vector<int>> &pairs)
        {
            // Step 1: Build adjacency list and degree counters
            unordered_map<int, vector<int>> adj;
            unordered_map<int, int> indegree, outdegree;

            for (auto &edge : pairs)
            {
                int u = edge[0];
                int v = edge[1];
                adj[u].push_back(v);
                outdegree[u]++;
                indegree[v]++;
            }

            // Step 2: Find start node for Eulerian path
            int start = pairs[0][0];
            for (auto &[node, _] : adj)
            {
                if (outdegree[node] - indegree[node] == 1)
                {
                    start = node;
                    break;
                }
            }

            // Step 3: Perform Hierholzer’s Algorithm (iterative DFS)
            vector<int> path;
            stack<int> st;
            st.push(start);

            while (!st.empty())
            {
                int curr = st.top();

                if (!adj[curr].empty())
                {
                    int next = adj[curr].back();
                    adj[curr].pop_back();
                    st.push(next);
                }
                else
                {
                    path.push_back(curr);
                    st.pop();
                }
            }

            // Step 4: Build result as list of edges
            reverse(path.begin(), path.end());

            vector<vector<int>> result;
            for (int i = 0; i < path.size() - 1; i++)
            {
                result.push_back({path[i], path[i + 1]});
            }

            return result;
        }
    };
