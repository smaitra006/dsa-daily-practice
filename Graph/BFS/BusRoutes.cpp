#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Bus Routes (LeetCode 815)
================================================================================
Task:
    You are given an array routes representing bus routes, where routes[i] is a
    bus route that the ith bus repeats forever.

    - If you are at a bus stop 'source', you can travel to another bus stop if
      there is a bus that connects both stops.
    - Return the least number of buses you must take to travel from source to target.
    - If it is not possible, return -1.

--------------------------------------------------------------------------------
Approach (BFS on Buses):
    1. Build a mapping from bus stop → buses that serve that stop.
    2. Use BFS where each level represents taking one more bus.
        - Start with all buses serving the `source` stop.
        - For each bus, traverse all its stops:
            - If the target is reached, return the current number of buses taken.
            - Otherwise, enqueue all unvisited buses that can be boarded at those stops.
    3. Keep a visited array for buses (not stops) to avoid re-processing buses.
    4. If BFS ends without reaching target → return -1.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = number of buses, and M = total number of stops across all routes.
    Time Complexity:  O(N * M) in worst case (each bus-stop pair processed once).
    Space Complexity: O(N + M) for visited arrays and mappings.
================================================================================
*/

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target)
    {
        if (source == target) return 0;
        int n = routes.size();

        // Map each stop to the list of buses passing through it
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            for (int stop : routes[i]) {
                mp[stop].push_back(i);
            }
        }

        // If source stop is not served by any bus → unreachable
        if (!mp.count(source)) return -1;

        queue<int> q;
        vector<bool> visited(n, false);

        // Start BFS with all buses that serve the source stop
        for (int bus : mp[source]) {
            q.push(bus);
            visited[bus] = true;
        }

        int taken = 1; // Number of buses taken so far

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                int currBus = q.front();
                q.pop();

                for (auto stop : routes[currBus]) {
                    if (stop == target) return taken; // Reached destination

                    // Try all buses passing through this stop
                    for (int nextBus : mp[stop]) {
                        if (!visited[nextBus]) {
                            visited[nextBus] = true;
                            q.push(nextBus);
                        }
                    }
                }
            }
            taken++; // Move to next level (taking another bus)
        }
        return -1; // Destination unreachable
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output:
    2
Explanation:
    Take bus 0 (stops at [1,2,7]) from stop 1 to stop 7,
    then switch to bus 1 (stops at [3,6,7]) to reach stop 6.

--------------------------------------------------------------------------------
Input:
    routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output:
    -1
Explanation:
    No sequence of buses connects stop 15 to stop 12.
================================================================================
*/

