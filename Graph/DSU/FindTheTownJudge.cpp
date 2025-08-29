#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Find the Town Judge (LeetCode 997)
//
// Task:
// In a town of n people labeled from 1 to n, there is a "judge" who:
// 1. Everyone else trusts the judge.
// 2. The judge trusts nobody.
//
// Given an array trust where trust[i] = [a, b] means person a trusts person b,
// find the judge or return -1 if no judge exists.
//
// Approach:
// 1. Use indegree and outdegree arrays for all n people.
//    - indegree[i] = number of people who trust person i
//    - outdegree[i] = number of people person i trusts
// 2. The judge must have indegree = n - 1 and outdegree = 0.
//==============================================================================

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust)
    {
        vector<int> indegree(n + 1, 0), outdegree(n + 1, 0);

        // Build indegree and outdegree arrays
        for (auto& t : trust) {
            outdegree[t[0]]++;
            indegree[t[1]]++;
        }

        // Check each person
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == n - 1 && outdegree[i] == 0) {
                return i;
            }
        }

        return -1; // no judge found
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(T + N), where T = trust.size(), N = number of people
// - Space: O(N) for indegree and outdegree arrays
//
// Example:
// Input: n = 3, trust = [[1,3],[2,3]]
// Output: 3
//==============================================================================
