#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem    : Time Needed to Inform All Employees
// Leetcode   : 1376
// Algorithm  : BFS (Level Order Traversal)
// Time Comp. : O(N)   → each employee visited once
// Space Comp.: O(N)   → adjacency list + queue
//==============================================================================

class Solution {
public:
    int ans = INT_MIN;  // stores maximum time taken to inform

    //------------------------------------------------------------------------------
    // BFS to propagate information from headID to all subordinates
    //------------------------------------------------------------------------------
    void bfs(unordered_map<int, vector<int>>& adj, vector<int>& informTime, int headID)
    {
        queue<pair<int, int>> q;   // {employee_id, time_taken}
        q.push({ headID, 0 });

        while (!q.empty()) {
            int curr_emp = q.front().first;
            int curr_time = q.front().second;
            q.pop();

            ans = max(ans, curr_time);

            for (int& ngbr : adj[curr_emp]) {
                q.push({ ngbr, curr_time + informTime[curr_emp] });
            }
        }
    }

    //------------------------------------------------------------------------------
    // Main function
    //------------------------------------------------------------------------------
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime)
    {
        unordered_map<int, vector<int>> adj;

        // Build adjacency list: manager → list of direct reports
        for (int i = 0; i < manager.size(); i++) {
            int manager_i = manager[i];
            if (manager_i != -1) {
                adj[manager_i].push_back(i);
            }
        }

        bfs(adj, informTime, headID);
        return ans;
    }
};

//==============================================================================
// Example Usage:
// Input : n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
// Output: 1
// Explanation: Head (2) takes 1 min to inform subordinates. Others need no extra time.
//==============================================================================
