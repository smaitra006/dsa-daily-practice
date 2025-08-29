#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Maximal Network Rank (LeetCode 1615)
//
// Task:
// Given an undirected graph with n cities and roads[i] = [a, b] representing
// a road between city a and city b, the "network rank" of two cities is defined as:
//     degree[a] + degree[b] - (1 if road exists between a and b else 0).
//
// The goal is to return the maximal network rank of all pairs of different cities.
//
// Approach:
// 1. Maintain degree[i] = number of roads connected to city i.
// 2. Store all roads in a set for O(1) lookup of direct connections.
// 3. For every pair of cities (i, j), compute rank = degree[i] + degree[j],
//    subtract 1 if there is a direct road between them.
// 4. Track the maximum rank encountered.
//==============================================================================

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads)
    {
        vector<int> degree(n, 0);
        set<pair<int, int>> road_set;

        // Build degree count and road set
        for (auto& road : roads) {
            degree[road[0]]++;
            degree[road[1]]++;
            road_set.insert({ road[0], road[1] });
            road_set.insert({ road[1], road[0] });
        }

        int max_rank = 0;

        // Evaluate all city pairs
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int rank = degree[i] + degree[j];
                if (road_set.find({ i, j }) != road_set.end()) {
                    rank--; // subtract if directly connected
                }
                max_rank = max(max_rank, rank);
            }
        }

        return max_rank;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N^2 + R), where R = roads.size(), N = number of cities
//         (since we check all pairs of cities).
// - Space: O(N + R), for degree array and road_set.
//
// Example:
// Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
// Output: 4
// Explanation: The pair (1,3) has maximal rank = 4.
//==============================================================================
