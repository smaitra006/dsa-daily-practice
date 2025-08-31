#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Merge Intervals (LeetCode 56)
//
// Task:
// Given an array of intervals where intervals[i] = [start, end], merge all
// overlapping intervals and return an array of the non-overlapping intervals
// that cover all the intervals in the input.
//
// Example:
//   Input:  intervals = [[1,3],[2,6],[8,10],[15,18]]
//   Output: [[1,6],[8,10],[15,18]]
//
//   Input:  intervals = [[1,4],[4,5]]
//   Output: [[1,5]]
//
// Approach (Sorting + Greedy Merge):
// 1. Sort intervals by their starting time.
// 2. Initialize result with the first interval.
// 3. Traverse through intervals:
//      - If current interval overlaps with the last one in result → merge them.
//      - Otherwise, push current interval into result.
// 4. Return the merged result.
//==============================================================================

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        if (intervals.empty()) return {};

        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result;

        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            if (result.back()[1] >= intervals[i][0]) {
                // Overlapping intervals → merge
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            }
            else {
                result.push_back(intervals[i]);
            }
        }

        return result;
    }
};

//==============================================================================
// Complexity Analysis:
// - Sorting: O(N log N), where N = number of intervals.
// - Merging: O(N), single pass through intervals.
// - Total: O(N log N).
// - Space: O(N) for storing the merged result.
//
// Example Walkthrough:
// Input:  [[1,3],[2,6],[8,10],[15,18]]
// Sorted: [[1,3],[2,6],[8,10],[15,18]]
// Step1: Start with [1,3]
// Step2: Merge [2,6] → [1,6]
// Step3: No overlap → add [8,10]
// Step4: No overlap → add [15,18]
// Output: [[1,6],[8,10],[15,18]]
//==============================================================================
