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
