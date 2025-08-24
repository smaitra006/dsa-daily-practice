#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Path with Maximum Probability (LeetCode 1514)
//
// Task:
// Given a graph of n nodes (0 to n-1) and edges with success probabilities,
// find the maximum probability of reaching end_node from start_node. Each edge
// [u, v] has a success probability succProb[i].
//
// Approach (Modified Dijkstra with Probabilities):
// - Build adjacency list: mp[u] = {v, probability}.
// - Use max-heap priority_queue storing {currentProbability, node}.
// - For each neighbor v of current node:
//      - If currProbability * edgeProbability > prob[v], update prob[v] and push to heap.
// - Return prob[end_node].
//
// Complexity:
// - Time: O(E * log V) → each edge may be relaxed via heap
// - Space: O(V + E) for adjacency list + probability array
//==============================================================================

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node)
    {
        // Build adjacency list
        unordered_map<int, vector<pair<int, double>>> mp;
        for (int i = 0; i < edges.size(); i++) {
            mp[edges[i][0]].push_back({ edges[i][1], succProb[i] });
            mp[edges[i][1]].push_back({ edges[i][0], succProb[i] });
        }

        // Probability array and max-heap
        vector<double> prob(n, 0.0);
        priority_queue<pair<double, int>> pq;

        prob[start_node] = 1.0;
        pq.push({ 1.0, start_node });

        while (!pq.empty()) {
            auto [currprob, currver] = pq.top();
            pq.pop();

            for (auto& [neighbor, edgeProb] : mp[currver]) {
                double newProb = currprob * edgeProb;
                if (newProb > prob[neighbor]) {
                    prob[neighbor] = newProb;
                    pq.push({ newProb, neighbor });
                }
            }
        }

        return prob[end_node];
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     vector<vector<int>> edges = {{0,1},{1,2},{0,2}};
//     vector<double> succProb = {0.5, 0.5, 0.2};
//     int n = 3, start_node = 0, end_node = 2;
//
//     cout << sol.maxProbability(n, edges, succProb, start_node, end_node) << endl;
//     // Expected Output: 0.25
//
// Explanation:
// Path 0→1→2 probability = 0.5 * 0.5 = 0.25
// Path 0→2 probability = 0.2
// Maximum probability = 0.25
//==============================================================================
