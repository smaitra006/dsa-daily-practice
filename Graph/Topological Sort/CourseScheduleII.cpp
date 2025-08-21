#include <bits/stdc++.h>
using namespace std;

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

class Solution
{
public:
    // Helper function to perform Kahn's Topological Sort
    void topologicalSort(int numCourses, vector<vector<int>>& adj, vector<int>& indegree, vector<int>& topo)
    {
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

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> adj(numCourses); // Adjacency list
        vector<int> indegree(numCourses, 0); // Indegree array

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
