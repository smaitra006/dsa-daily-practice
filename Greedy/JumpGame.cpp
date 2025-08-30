#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Jump Game (LeetCode 55)
//
// Task:
// You are given an integer array `nums` where `nums[i]` represents the maximum
// jump length from index i. Initially, you are positioned at the first index.
// Return true if you can reach the last index, or false otherwise.
//
// Example:
//   Input:  nums = [2,3,1,1,4]
//   Output: true
//   Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
//
//   Input:  nums = [3,2,1,0,4]
//   Output: false
//
// Approach (Greedy Backward Traversal):
// 1. Start from the last index (`end_point = n - 1`).
// 2. Traverse backwards from right to left.
// 3. For each index `i`, check if from `i` we can reach `end_point`:
//      - If nums[i] >= (end_point - i), then update end_point = i.
// 4. At the end, if end_point == 0, we can reach the last index.
//==============================================================================

class Solution {
public:
    bool canJump(vector<int>& nums)
    {
        int n = nums.size();
        int end_point = n - 1;

        for (int i = n - 1; i >= 0; i--) {
            int step = end_point - i;
            if (nums[i] >= step) {
                end_point = i;
            }
        }

        return end_point == 0;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(N), where N = size of nums (single pass from right to left).
// - Space: O(1), only variables used.
//
// Example Walkthrough:
// Input: nums = [2,3,1,1,4]
// end_point = 4
// i=4: nums[4]=4 >=0 → end_point=4
// i=3: nums[3]=1 >=1 → end_point=3
// i=2: nums[2]=1 <1 → no change
// i=1: nums[1]=3 >=2 → end_point=1
// i=0: nums[0]=2 >=1 → end_point=0
// Result: true
//==============================================================================
