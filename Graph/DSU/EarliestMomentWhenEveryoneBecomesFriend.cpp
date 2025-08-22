#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Earliest Moment When Everyone Becomes Friends (LeetCode 1101)
================================================================================
Task:
    There are n people in a social group labeled from 0 to n-1. You are given
    a list of logs where each log[i] = [timestamp, x, y] indicates that
    person x and person y became friends at time timestamp.

    Friendship is transitive: if a is friends with b, and b is friends with c,
    then a is also friends with c.

    Return the earliest time at which everyone became friends. If it is
    impossible, return -1.

--------------------------------------------------------------------------------
Key Insight:
    - This is a classic connectivity problem.
    - Use Disjoint Set Union (Union-Find) to gradually merge friendships.
    - After processing all logs in chronological order, check when the entire
      graph becomes a single connected component.

--------------------------------------------------------------------------------
Approach (DSU):
    1. Sort logs by timestamp.
    2. Use DSU to union the two people in each log.
    3. Track the number of connected components.
    4. When components reduce to 1, return the current timestamp.
    5. If after all logs, components > 1 → return -1.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let n = number of people, m = number of logs.

    Time Complexity:  O(m log m + m * α(n))
        - Sorting logs → O(m log m)
        - Union-Find operations (amortized inverse Ackermann, ~O(1)).

    Space Complexity: O(n)
        - DSU parent and rank arrays.
================================================================================
*/

class DSU {
private:
    vector<int> parent, rank;
    int components;  // track number of connected components

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        components = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // path compression
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);

        if (px == py) return false;

        // union by rank
        if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else {
            parent[py] = px;
            rank[px]++;
        }

        components--; // one less component after successful merge
        return true;
    }

    int getComponents()
    {
        return components;
    }
};

class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int n)
    {
        // Step 1: Sort logs by timestamp
        sort(logs.begin(), logs.end());

        DSU dsu(n);

        // Step 2: Process logs in chronological order
        for (auto& log : logs) {
            int time = log[0], a = log[1], b = log[2];
            dsu.unite(a, b);

            // Step 3: If everyone connected, return time
            if (dsu.getComponents() == 1) {
                return time;
            }
        }

        // Step 4: Not everyone connected
        return -1;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    logs = [
        [20190101,0,1],
        [20190104,3,4],
        [20190107,2,3],
        [20190211,1,5],
        [20190224,2,4],
        [20190301,0,3],
        [20190312,1,2],
        [20190322,4,5]
    ], n = 6

Output:
    20190301

Explanation:
    - By 20190301, all 6 people become connected as one group.
================================================================================
*/
