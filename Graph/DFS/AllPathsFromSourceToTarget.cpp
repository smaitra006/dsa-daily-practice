#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 797: ALL PATHS FROM SOURCE TO TARGET
 * =================================================================== */

 /**
  * @brief Find all paths from node 0 to node n - 1 in a DAG (Directed Acyclic Graph)
  *
  * PROBLEM STATEMENT:
  * Given a directed acyclic graph (DAG) with `n` nodes labeled from 0 to n - 1,
  * return all possible paths from node `0` to node `n - 1`.
  *
  * The graph is represented as an adjacency list: graph[i] contains all nodes
  * reachable from node i.
  *
  * INPUT:
  * - vector<vector<int>> graph: Adjacency list of a DAG
  *
  * OUTPUT:
  * - vector<vector<int>>: All valid paths from 0 to n - 1
  *
  * EXAMPLE:
  * Input: graph = [[1,2],[3],[3],[]]
  * Output: [[0,1,3],[0,2,3]]
  *
  * ALGORITHM (DFS + Backtracking):
  * - Perform DFS starting from node 0
  * - Track the path using a vector
  * - When reaching node n - 1, store the path in result
  * - Backtrack after each call to explore all branches
  *
  * NOTE: Since the graph is a DAG, we do NOT need a `visited[]` array.
  *          There are no cycles, so revisiting is not a problem.
  *
  * COMPLEXITY:
  * - Time: O(2^N) worst case (exponential number of paths)
  * - Space: O(N) call stack + O(#paths * avgPathLength) for result
  */

class Solution
{
public:
    /**
     * @brief DFS to explore all paths from source to target
     */
    void dfs(vector<vector<int>>& graph, int node,
        vector<vector<int>>& result, vector<int>& path)
    {

        path.push_back(node);

        if (node == graph.size() - 1) {
            result.push_back(path); // Reached destination
        }
        else {
            for (int neighbor : graph[node]) {
                dfs(graph, neighbor, result, path);
            }
        }

        path.pop_back(); // Backtrack
    }

    /**
     * @brief Main function to compute all paths from node 0 to n - 1
     */
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
    {
        vector<vector<int>> result;
        vector<int> path;

        dfs(graph, 0, result, path);

        return result;
    }
};

