#include <bits/stdc++.h>
using namespace std;

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

class Solution
{
public:
    // Helper function to check if graph is DAG using Kahn's Algorithm
    bool isDAG(vector<vector<int>>& adj, vector<int>& indegree)
    {
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

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
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
