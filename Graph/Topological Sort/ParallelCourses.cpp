#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Parallel Courses III (LeetCode 2050)
================================================================================
Task:
    There are n courses labeled from 1 to n. You are given:
      - time[i]: the time needed to complete the i-th course.
      - relations: prerequisite relations (u, v) meaning course u must be done
        before course v.

    You can take multiple courses simultaneously if prerequisites are satisfied.
    Return the minimum time to complete all courses.

--------------------------------------------------------------------------------
Approach (Topological Sort - Kahn’s Algorithm):
    1. Build adjacency list and indegree array from relations.
    2. Initialize queue with courses having no prerequisites.
       - Set their completion time as `time[i]`.
    3. Process courses in topological order:
       - For each neighbor, update its `maxTime[neighbor]` as the maximum of:
            (current maxTime[neighbor], maxTime[curr] + time[neighbor]).
       - Decrement indegree of neighbor.
       - If indegree reaches 0, push into queue.
    4. The answer is the maximum completion time among all courses.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = number of courses, M = number of relations.

    Time Complexity:  O(N + M)
        - Build graph: O(M)
        - Topological traversal: O(N + M)

    Space Complexity: O(N + M)
        - Adjacency list + indegree + maxTime arrays.
================================================================================
*/

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time)
    {
        // Step 1: Build adjacency list and indegree array
        vector<vector<int>> adj(n);
        vector<int> indegree(n, 0);
        for (auto& r : relations) {
            int u = r[0] - 1;  // convert to 0-index
            int v = r[1] - 1;
            adj[u].push_back(v);
            indegree[v]++;
        }

        // Step 2: Initialize queue with courses having no prerequisites
        queue<int> q;
        vector<int> maxTime(n, 0);
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                maxTime[i] = time[i];
            }
        }

        // Step 3: Topological traversal
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (int neighbour : adj[curr]) {
                maxTime[neighbour] = max(maxTime[neighbour], maxTime[curr] + time[neighbour]);
                indegree[neighbour]--;
                if (indegree[neighbour] == 0) {
                    q.push(neighbour);
                }
            }
        }

        // Step 4: Result is the maximum completion time
        return *max_element(maxTime.begin(), maxTime.end());
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 3
    relations = [[1,3],[2,3]]
    time = [3,2,5]

Output:
    8

Explanation:
    - Course 1 takes 3 units, course 2 takes 2 units.
    - Both must be done before course 3 (takes 5 units).
    - Total = max(3,2) + 5 = 8.
--------------------------------------------------------------------------------
Notes:
    - This is a **DAG longest path problem** solved via Topological Sort.
    - Unlike shortest path, here we accumulate maximum times.
================================================================================
*/
