#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Jump Game II (LeetCode 45)
//
// Task:
// You are given a 0-indexed array `nums` of length n where `nums[i]` represents
// the maximum jump length from index i. Your goal is to reach the last index
// in the minimum number of jumps.
//
// Return the minimum number of jumps to reach the last index. You can assume
// that you can always reach the last index.
//
// Example:
//   Input:  nums = [2,3,1,1,4]
//   Output: 2
//   Explanation: Jump 1 step to index 1, then 3 steps to the last index.
//
//   Input:  nums = [2,3,0,1,4]
//   Output: 2
//
// Approach (Greedy - Level Traversal):
// 1. Maintain two pointers: `end` (end of current jump range) and `farthest`
//    (the farthest index reachable in the current range).
// 2. Iterate through the array (except the last index):
//      - Update `farthest` as the max reach from current index.
//      - If we reach `end`, it means we must make a jump:
//          - Increment jumps
//          - Update `end = farthest`
// 3. At the end, the number of jumps will be the minimum required.
//==============================================================================

class Solution {
public:
    int jump(vector<int>& nums)
    {
        int n = nums.size();
        int jumps = 0;
        int end = 0, farthest = 0;

        for (int i = 0; i < n - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            if (i == end) {
                jumps++;
                end = farthest;
            }
        }

        return jumps;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = size of nums (each index processed once).
// - Space: O(1), only counters used.
//
// Example Walkthrough:
// Input: nums = [2,3,1,1,4]
// i=0: farthest=max(0,0+2)=2 → end=0 → jump=1, end=2
// i=1: farthest=max(2,1+3)=4
// i=2: farthest=max(4,2+1)=4 → i==end(2)? yes → jump=2, end=4
// Loop ends (i < n-1)
// Output: 2
//==============================================================================
