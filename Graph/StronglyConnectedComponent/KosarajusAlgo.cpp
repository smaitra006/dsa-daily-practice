#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * TOPIC: STRONGLY CONNECTED COMPONENTS (Kosaraju's Algorithm)
 * =================================================================== */

 /**
  * @brief Identify Strongly Connected Components (SCCs) in a directed graph
  *
  * DEFINITION:
  * A **Strongly Connected Component (SCC)** is a maximal subgraph of a directed graph
  * where every node is reachable from every other node in that subgraph.
  *
  * PROBLEM:
  * Given a directed graph with `V` vertices and `E` edges,
  * return the number of strongly connected components.
  *
  * APPLICATIONS:
  * - Optimizing compilers (function/module dependencies)
  * - Social networks (mutual follower clusters)
  * - Circuit analysis (feedback loops)
  * - Web page link analysis (PageRank)
  *
  * ALGORITHM: KOSARAJU'S ALGORITHM (3 steps)
  * 1. Do DFS and push nodes onto a stack (in postorder, i.e., finish time)
  * 2. Reverse the entire graph
  * 3. Pop nodes from the stack, and do DFS on reversed graph to find components
  *
  * COMPLEXITY:
  * - Time: O(V + E)
  * - Space: O(V + E)
  */

class Solution
{
public:
    /**
     * Step 1: DFS to fill stack in post-order
     */
    void dfs1(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st)
    {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs1(neighbor, adj, visited, st);
            }
        }

        st.push(node); // Post-order push
    }

    /**
     * Step 2: DFS on the transposed graph
     */
    void dfs2(int node, vector<vector<int>>& revAdj, vector<bool>& visited)
    {
        visited[node] = true;

        for (int neighbor : revAdj[node]) {
            if (!visited[neighbor]) {
                dfs2(neighbor, revAdj, visited);
            }
        }
    }

    /**
     * @brief Main function to compute number of strongly connected components
     */
    int kosarajuSCC(int V, vector<vector<int>>& adj)
    {
        stack<int> st;
        vector<bool> visited(V, false);

        // Step 1: Do a DFS and fill stack with vertices by finish time
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs1(i, adj, visited, st);
            }
        }

        // Step 2: Reverse the graph
        vector<vector<int>> revAdj(V);
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                revAdj[v].push_back(u); // Reverse the edge
            }
        }

        // Step 3: Process all nodes in reverse postorder (stack) and count SCCs
        fill(visited.begin(), visited.end(), false);
        int count = 0;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                dfs2(node, revAdj, visited);
                count++;
            }
        }

        return count; // Number of strongly connected components
    }
};
