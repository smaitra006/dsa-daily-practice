#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Is Graph Bipartite? (LeetCode 785)
================================================================================
Task:
    Given an undirected graph where graph[i] is a list of all nodes adjacent to i,
    determine if the graph is bipartite.

    - A graph is bipartite if its vertices can be divided into two disjoint sets
      such that every edge connects a vertex in one set to a vertex in the other set.
    - Equivalently: we can "color" the graph with two colors such that no two
      adjacent nodes share the same color.

--------------------------------------------------------------------------------
Key Insight:
    - This is a graph coloring problem.
    - If we can assign two colors consistently without conflict, the graph is bipartite.
    - If at any point, a node and its neighbor require the same color → not bipartite.

--------------------------------------------------------------------------------
Approach (DFS Coloring):
    1. Initialize a color array with -1 (uncolored).
    2. For each unvisited node, run DFS:
        - Assign it a color (0 or 1).
        - For each neighbor:
            - If same color as current → return false.
            - If uncolored, recursively DFS with opposite color.
    3. If all nodes can be colored consistently → return true.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let V = number of nodes, E = number of edges.
    - Time Complexity:  O(V + E)
        Each node and edge is processed once.
    - Space Complexity: O(V)
        Color array + recursion stack.
================================================================================
*/

class Solution {
public:
    // Helper: DFS to check bipartiteness
    bool dfsBipartite(vector<vector<int>>& graph, vector<int>& color, int node, int curr_color)
    {
        color[node] = curr_color;

        for (auto neighbour : graph[node]) {
            // If neighbor has same color → conflict
            if (color[neighbour] == curr_color) {
                return false;
            }
            // If neighbor is uncolored, DFS with opposite color
            if (color[neighbour] == -1) {
                if (!dfsBipartite(graph, color, neighbour, 1 - curr_color)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph)
    {
        int n = graph.size();
        vector<int> color(n, -1);  // -1 = uncolored, 0/1 = two colors

        // Run DFS on every component (graph may be disconnected)
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!dfsBipartite(graph, color, i, 0)) {
                    return false;
                }
            }
        }
        return true;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    graph = [[1,2,3],[0,2],[0,1,3],[0,2]]

Output:
    false

Explanation:
    - Graph contains an odd cycle (0-1-2-0).
    - Cannot 2-color without conflict → not bipartite.
================================================================================
*/

