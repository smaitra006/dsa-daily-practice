#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Alien Dictionary (LeetCode 269)
================================================================================
Task:
    There is a new alien language that uses the English alphabet but in a
    different order. You are given a list of words sorted lexicographically
    according to the alien language. Determine a possible order of the
    characters. If there is no valid order, return "".

--------------------------------------------------------------------------------
Approach (Topological Sort using BFS - Kahn's Algorithm):
    1. Build graph (adjacency list) of characters:
        - Compare adjacent words.
        - Find first differing character → that gives ordering (u → v).
        - If invalid (e.g., ["abc", "ab"]) → return "".
    2. Track indegree of each node.
    3. Perform Kahn's BFS topological sort:
        - Start with all nodes having indegree 0.
        - Repeatedly pop from queue, append to result, reduce indegrees.
    4. If result length < total unique chars → cycle exists → return "".

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = number of words, K = total length of all words, C = unique characters.

    Time Complexity:  O(K + C)
        - Building graph requires comparing adjacent words (O(K)).
        - BFS topological sort processes each node/edge once.

    Space Complexity: O(C + E)
        - For adjacency list and indegree map.
================================================================================
*/

class Solution {
public:
    string alienOrder(vector<string>& words)
    {
        unordered_map<char, vector<char>> adj;   // adjacency list
        unordered_map<char, int> indegree;       // indegree count

        // Step 1: Initialize indegree map with all unique characters
        for (auto& w : words) {
            for (char c : w) {
                indegree[c] = 0;
            }
        }

        // Step 2: Build graph by comparing adjacent words
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i + 1];
            int len = min(w1.size(), w2.size());
            bool found = false;

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    adj[w1[j]].push_back(w2[j]);
                    indegree[w2[j]]++;
                    found = true;
                    break;
                }
            }

            // Invalid case: prefix issue (e.g., ["abc", "ab"])
            if (!found && w1.size() > w2.size()) return "";
        }

        // Step 3: Topological sort (Kahn's Algorithm)
        queue<char> q;
        for (auto& [ch, deg] : indegree) {
            if (deg == 0) q.push(ch);
        }

        string result;
        while (!q.empty()) {
            char curr = q.front(); q.pop();
            result.push_back(curr);

            for (char nxt : adj[curr]) {
                indegree[nxt]--;
                if (indegree[nxt] == 0) q.push(nxt);
            }
        }

        // Step 4: Validate (check cycle)
        if (result.size() < indegree.size()) return "";

        return result;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    words = ["wrt", "wrf", "er", "ett", "rftt"]

Output:
    "wertf"

Explanation:
    - 'w' → 'e' (from "wrt" vs "er")
    - 'r' → 't' (from "er" vs "ett")
    - 't' → 'f' (from "ett" vs "rftt")
    A valid order is "wertf".
--------------------------------------------------------------------------------
Notes:
    - If multiple valid orders exist, any one is acceptable.
    - If cycle or invalid prefix, return "".
    - This is essentially a Topological Sorting problem.
================================================================================
*/
